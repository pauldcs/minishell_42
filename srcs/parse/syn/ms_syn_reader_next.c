/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_syn_reader_next.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 01:50:33 by nmathieu          #+#    #+#             */
/*   Updated: 2022/06/30 14:39:26 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms/parse/syn_reader.h"
#include "ms/parse/tok_reader.h"
#include "ms/parse/parse_errors.h"
#include "ms/parse/syner.h"
#include "ms/utils/io.h"
#include "ms/state.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

static int	read_here_docs(t_ms_syn_reader *self)
{
	int			ret;
	char		*delim;
	int			result;
	t_ms_str	contents;

	result = 0;
	while (true)
	{
		delim = ms_syner_here_doc(&self->syner);
		if (!delim)
			break ;
		if (result == 0)
			result = 1;
		ret = ms_tok_reader_here_doc(&self->tokens, delim, &contents);
		if (ret == -1)
			return (-1);
		if ((ret == 2 || ret == 3) && result == 1)
			result = 2;
		if (ret == 3)
			ms_parse_err_here_doc(self->tokens.line + 1, delim);
		if (!ms_syner_submit_here_doc(&self->syner, contents))
			return (-1);
		free((void *)contents.s);
	}
	return (result);
}

static int	update_token(t_ms_syn_reader *self)
{
	int	ret;

	if (!self->reuse_token)
	{
		ret = ms_tok_reader_next(&self->tokens, &self->last_token);
		if (ret == -1 || ret == 0)
			return (ret);
		if (self->last_token.kind == MS_TOK_NEWLINE
			|| self->last_token.kind == MS_TOK_EOF)
		{
			ret = read_here_docs(self);
			if (ret == -1)
				return (-1);
			if (ret == 1)
				self->reuse_token = true;
			if (ret == 2 || ret == 3)
				self->last_token.kind = MS_TOK_EOF;
		}
		else if (self->last_token.kind & MS_TOK_ERR_MASK)
			return (ms_parse_err_token_err(self->tokens.line + 1,
					&self->last_token), -1);
	}
	else
		self->reuse_token = false;
	return (1);
}

static void	token_err(t_ms_syn_reader *self)
{
	ms_parse_err_token(self->tokens.line + 1, &self->last_token);
}

int	ms_syn_reader_next(t_ms_syn_reader *self, t_ms_syn *result)
{
	int			ret;

	if (self->exhausted)
		return (0);
	while (true)
	{
		ret = update_token(self);
		if (ret == -1 || ret == 0)
			return (ret);
		ret = ms_syner_absorbe(&self->syner, &self->last_token, result);
		if (ret == MS_SYN_R_FAILURE)
			return (-1);
		if (ret == MS_SYN_R_UNEXPECTED_TOKEN)
			return (token_err(self), 0);
		if (ret == MS_SYN_R_INCOMPLETE)
			continue ;
		if (ret == MS_SYN_R_SUCCESS_PRESERVE)
			self->reuse_token = true;
		if (self->last_token.kind == MS_TOK_EOF && result->kind == MS_SYN_END)
			self->exhausted = true;
		return (1);
	}
}
