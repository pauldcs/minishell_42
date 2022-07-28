/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 15:47:10 by nmathieu          #+#    #+#             */
/*   Updated: 2022/07/06 13:49:50 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms/state.h"
#include "ms/parse/parse_errors.h"
#include "ms/utils/debug.h"
#include "ms/utils/io.h"
#include <stdint.h>

static const char	*g_tok_names[] = {
	"end of file",
	"newline",
	NULL,
	"&&",
	"|",
	"||",
	"<",
	"<<",
	">",
	">>",
	"(",
	")",
};

static const char	*g_tok_errs[] = {
	"unexpected EOF while looking for matching '\''",
	"unexpected EOF while looking for matching '\"'",
};

void	ms_parse_err_token(size_t line, t_ms_tok *tok)
{
	ms_puterr(g_ms.exec_name);
	if (line != 0)
	{
		ms_puterr(": line ");
		ms_putnbr_err(line);
	}
	ms_puterr(": syntax error near unexpected token '");
	if (tok->kind == MS_TOK_WORD)
		ms_putderr(tok->slice);
	else
		ms_puterr(g_tok_names[tok->kind]);
	ms_puterr("'\n");
}

void	ms_parse_err_token_err(size_t line, t_ms_tok *tok)
{
	ms_assert(tok->kind & MS_TOK_ERR_MASK, "can't display a non-error token");
	ms_puterr(g_ms.exec_name);
	if (line != 0)
	{
		ms_puterr(": line ");
		ms_putnbr_err(line);
	}
	ms_puterr(": ");
	ms_puterr(g_tok_errs[tok->kind & ~MS_TOK_ERR_MASK]);
	ms_puterr("\n");
}

void	ms_parse_err_here_doc(size_t line, char *delim)
{
	ms_puterr(g_ms.exec_name);
	if (line != 0)
	{
		ms_puterr(": line ");
		ms_putnbr_err(line);
	}
	ms_puterr(": warning: here-document delimited by end-of-file (wanted '");
	ms_putderr(delim);
	ms_puterr("')\n");
}

void	ms_parse_err_ambiguous_redirect(char *filename)
{
	ms_puterr(g_ms.exec_name);
	ms_puterr(": ");
	ms_putderr(filename);
	ms_puterr(": ambiguous redirect\n");
}
