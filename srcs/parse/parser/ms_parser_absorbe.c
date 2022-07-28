/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser_absorbe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 00:04:26 by nmathieu          #+#    #+#             */
/*   Updated: 2022/06/30 10:15:56 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms/parse/parser.h"
#include "ms/utils/debug.h"
#include "./ms_parser_absorbe.h"

static void	init_result(t_ms_parser *self, t_ms_ast **result)
{
	*result = self->result;
	self->result = NULL;
	self->scopes.len = 1;
	self->scopes.buf[0] = &self->result;
	ms_assert(self->parens.len == 0, "finished AST without parens.len == 0");
}

t_ms_parse_r	ms_parser_absorbe(
					t_ms_parser *self,
					t_ms_syn *syn,
					t_ms_ast **result)
{
	if (syn->kind == MS_SYN_CMD && !ms_parser_add_cmd(self, &syn->cmd))
		return (ms_syn_free(syn), MS_PARSE_R_FAILURE);
	else if (syn->kind == MS_SYN_AND_IF
		&& !ms_parser_add_binop(self, MS_AST_AND_IF))
		return (ms_syn_free(syn), MS_PARSE_R_FAILURE);
	else if (syn->kind == MS_SYN_OR_IF
		&& !ms_parser_add_binop(self, MS_AST_OR_IF))
		return (ms_syn_free(syn), MS_PARSE_R_FAILURE);
	else if (syn->kind == MS_SYN_PIPE
		&& !ms_parser_add_binop(self, MS_AST_PIPE))
		return (ms_syn_free(syn), MS_PARSE_R_FAILURE);
	else if (syn->kind == MS_SYN_SEQ
		&& !ms_parser_add_binop(self, MS_AST_SEQ))
		return (ms_syn_free(syn), MS_PARSE_R_FAILURE);
	else if (syn->kind == MS_SYN_OPAREN && !ms_parser_add_oparen(self))
		return (ms_syn_free(syn), MS_PARSE_R_FAILURE);
	else if (syn->kind == MS_SYN_CPAREN
		&& !ms_parser_add_cparen(self, &syn->cparen))
		return (ms_syn_free(syn), MS_PARSE_R_FAILURE);
	else if (syn->kind == MS_SYN_END)
		return (init_result(self, result), MS_PARSE_R_SUCCESS);
	return (MS_PARSE_R_INCOMPLETE);
}
