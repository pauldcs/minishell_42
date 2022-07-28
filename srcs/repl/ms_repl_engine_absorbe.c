/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_repl_engine_absorbe.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 12:19:57 by nmathieu          #+#    #+#             */
/*   Updated: 2022/07/12 16:04:03 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ms_repl_engine.h"
#include "ms/utils/debug.h"
#include "ms/utils/io.h"
#include "ms/state.h"
#include "ms/parse/parser.h"
#include "ms/parse/parse_errors.h"
#include <stdlib.h>
#include "ms/utils/alloc.h"
#include <stdint.h>

// -1  - An unexpected error occured.
//  0  - The here-doc is not yet finished. More lines are required.
//  1  - The here-doc is finished, no more lines are required.
static int	absorbe_here_doc(
				t_ms_repl_engine *self,
				const char **line,
				char *delim)
{
	if (!*line)
		ms_parse_err_here_doc(0, delim);
	if (!*line || ms_str_cmp(*line, delim) == 0)
	{
		ms_syner_submit_here_doc(
			&self->syner,
			(t_ms_str){self->here_doc.buf, self->here_doc.len});
		self->here_doc.len = 0;
		*line = "";
		return (1);
	}
	else
	{
		if (!ms_vec_append(
				(t_ms_vec *)&self->here_doc, *line, ms_str_len(*line), 1))
			return (-1);
		if (!ms_vec_reserve((t_ms_vec *)&self->here_doc, 1, sizeof(char)))
			return (-1);
		self->here_doc.buf[self->here_doc.len++] = '\n';
		return (0);
	}
}

// Consumes one character of a line of input.
//
// -2  - A parsing error occured.
// -1  - An unexpected error occured.
//  0  - A brand new line is requested.
//  1  - No more lines are required, `ast` has been initialized.
//  2  - The function should be called again, the line is not yet
//       totally consumed.
static int	consume_line(
				t_ms_repl_engine *self,
				const char **line,
				t_ms_ast **ast,
				bool *reuse_char)
{
	int	ret;

	if (!*line)
		ret = ms_repl_engine_absorbe_char(self, '\0', ast, reuse_char);
	else if (**line)
		ret = ms_repl_engine_absorbe_char(self, **line, ast, reuse_char);
	else
		ret = ms_repl_engine_absorbe_char(self, '\n', ast, reuse_char);
	if (ret < 0 || (!self->reuse_token && !*reuse_char && (!*line || !**line)))
		return (ret);
	if (!*reuse_char && !self->reuse_token)
		(*line)++;
	return (2);
}

// -2  - A parsing error occured.
// -1  - An unexpected error occured.
//  0  - Another line is required.
//  1  - No more lines are required, `ast` has been initialized.
static int	inner(t_ms_repl_engine *self, const char *line, t_ms_ast **ast)
{
	int			ret;
	bool		reuse_char;
	char		*delim;

	delim = ms_syner_here_doc(&self->syner);
	if (delim)
	{
		ret = absorbe_here_doc(self, &line, delim);
		if (ret <= 0)
			return (ret);
	}
	while (true)
	{
		ret = consume_line(self, &line, ast, &reuse_char);
		if (ret <= 1)
			return (ret);
	}
}

static bool	next_line(char **s, char **line)
{
	if (!**s)
		return (false);
	*line = *s;
	while (**s && **s != '\n')
		(*s)++;
	if (**s == '\n')
		*((*s)++) = '\0';
	return (true);
}

// -2  - A parsing error occured.
// -1  - An unexpected error occured.
//  0  - More data is required.
//  1  - No more data required.
int	ms_repl_engine_absorbe(
		t_ms_repl_engine *self,
		char *line,
		t_ms_ast **ast)
{
	char	*l;
	int		ret;

	if (!line || !*line)
		return (inner(self, line, ast));
	while (next_line(&line, &l))
	{
		ret = inner(self, l, ast);
		if (ret != 0)
			return (ret);
	}
	return (0);
}
