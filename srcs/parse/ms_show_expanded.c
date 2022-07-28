/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_show_expanded.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 01:05:01 by nmathieu          #+#    #+#             */
/*   Updated: 2022/07/04 12:23:39 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms/utils/str.h"
#include "ms/utils/io.h"
#include "ms/parse/token.h"
#include "ms/parse/tok_reader.h"
#include "ms/parse/lexer.h"
#include "ms/parse/expand.h"
#include "ms/utils/alloc.h"
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>

static const t_ms_str	g_names[] = {
{"EOF", 3},
{"NEWLINE", 7},
{"WORD", 4},
{"DAND", 4},
{"OR", 2},
{"DOR", 3},
{"LESS", 4},
{"DLESS", 5},
{"GREAT", 5},
{"DGREAT", 6},
{"OPAREN", 6},
{"CPAREN", 6},
};

static bool	ms_print_token(t_ms_tok *token, t_ms_vec *words)
{
	size_t	i;

	write(STDOUT_FILENO, g_names[token->kind].s, g_names[token->kind].len);
	if (token->kind == MS_TOK_WORD)
	{
		if (!ms_push_expanded(token->slice, words))
			return (false);
		i = 0;
		while (i < words->len)
		{
			write(STDOUT_FILENO, " (", 2);
			ms_putdstr(((char **)words->buf)[i]);
			write(STDOUT_FILENO, ")", 1);
			i++;
		}
		while (words->len)
			free(((char **)words->buf)[--words->len]);
	}
	write(STDOUT_FILENO, "\n", 1);
	return (true);
}

bool	inner(t_ms_vec *words, t_ms_tok_reader *reader)
{
	int			ret;
	t_ms_tok	token;

	while (true)
	{
		ret = ms_tok_reader_next(reader, &token);
		if (ret == -1)
			return (false);
		if (ret == 0)
			return (true);
		if (!ms_print_token(&token, words))
			return (false);
	}
}

bool	ms_show_expanded(int fd)
{
	t_ms_tok_reader	reader;
	t_ms_vec		words;
	bool			result;

	words.cap = 0;
	words.len = 0;
	ms_tok_reader_init(&reader, fd);
	result = inner(&words, &reader);
	if (words.cap)
		free(words.buf);
	ms_tok_reader_deinit(&reader);
	return (result);
}
