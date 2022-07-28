/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_repl_engine_absorbe_char.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 22:41:01 by nmathieu          #+#    #+#             */
/*   Updated: 2022/07/15 20:10:29 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "ms_repl_engine.h"
#include "ms/parse/lexer.h"
#include "ms/parse/parse_errors.h"
#include "ms/state.h"
#include "ms/utils/io.h"
#include <stdlib.h>

static void	reset(t_ms_repl_engine *self)
{
	self->lexer.state = MS_LEX_INIT;
	self->lexer.chars.len = 0;
	self->syner.state = MS_SYNER_INIT;
	self->syner.depth = 0;
	while (self->syner.iords.len)
		ms_iord_free(&self->syner.iords.buf[--self->syner.iords.len]);
	while (self->syner.args.len)
		free(self->syner.args.buf[--self->syner.args.len]);
	self->syner.here_docs.len = 0;
	self->syner.here_docs.complete = 0;
	ms_ast_free(self->parser.result);
	self->parser.result = NULL;
	self->parser.scopes.len = 1;
	self->parser.scopes.buf[0] = &self->parser.result;
	self->reuse_token = false;
}

static int	renew_token(t_ms_repl_engine *self, char c, bool *reuse_char)
{
	int	ret;

	if (self->reuse_token)
	{
		self->reuse_token = false;
		return (1);
	}
	*reuse_char = false;
	ret = ms_lexer_absorbe(&self->lexer, c, &self->token);
	if (ret == MS_LEX_R_FAILURE)
		return (-1);
	if (ret == MS_LEX_R_INCOMPLETE)
		return (0);
	if (ret == MS_LEX_R_SUCCESS_SAME)
		*reuse_char = true;
	if (self->token.kind == MS_TOK_NEWLINE && ms_syner_here_doc(&self->syner))
		return (0);
	if (self->token.kind & MS_TOK_ERR_MASK)
		return (ms_parse_err_token_err(0, &self->token), reset(self), -2);
	return (1);
}

// -2   - A parsing error occured.
// -1   - An unexpected error occured.
//  0   - Another character is requested (potentially the same one if
//        `reuse_char` has been set to `true`).
//  1   - A new `t_ast` has been generated.
int	ms_repl_engine_absorbe_char(
				t_ms_repl_engine *self,
				char c,
				t_ms_ast **ast,
				bool *reuse_char)
{
	int			ret;
	t_ms_syn	syn;

	ret = renew_token(self, c, reuse_char);
	if (ret <= 0)
		return (ret);
	ret = ms_syner_absorbe(&self->syner, &self->token, &syn);
	if (ret == MS_SYN_R_FAILURE)
		return (-1);
	if (ret == MS_SYN_R_INCOMPLETE)
		return (0);
	if (ret == MS_SYN_R_UNEXPECTED_TOKEN)
		return (ms_parse_err_token(0, &self->token), reset(self), -2);
	if (ret == MS_SYN_R_SUCCESS_PRESERVE)
		self->reuse_token = true;
	ret = ms_parser_absorbe(&self->parser, &syn, ast);
	if (ret == MS_PARSE_R_FAILURE)
		return (-1);
	if (ret == MS_PARSE_R_INCOMPLETE)
		return (0);
	return (1);
}
