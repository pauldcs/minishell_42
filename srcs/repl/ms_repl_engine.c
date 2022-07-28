/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_repl_engine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 12:13:10 by nmathieu          #+#    #+#             */
/*   Updated: 2022/07/25 20:33:41 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ms_repl_engine.h"
#include <stdlib.h>

bool	ms_repl_engine_init(t_ms_repl_engine *self)
{
	if (!ms_parser_init(&self->parser))
		return (false);
	ms_lexer_init(&self->lexer);
	ms_syner_init(&self->syner);
	self->reuse_token = false;
	self->here_doc.cap = 0;
	self->here_doc.len = 0;
	self->here_doc.buf = NULL;
	self->first_prompt = true;
	self->cmd_buf.buf = NULL;
	self->cmd_buf.len = 0;
	self->cmd_buf.cap = 0;
	return (true);
}

void	ms_repl_engine_deinit(t_ms_repl_engine *self)
{
	ms_parser_deinit(&self->parser);
	ms_lexer_deinit(&self->lexer);
	ms_syner_deinit(&self->syner);
	if (self->here_doc.cap)
		free(self->here_doc.buf);
	if (self->cmd_buf.cap)
		free(self->cmd_buf.buf);
}

void	ms_repl_engine_reset(t_ms_repl_engine *self)
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
	self->parser.parens.len = 0;
	self->first_prompt = true;
	ms_sigset_prompt();
}
