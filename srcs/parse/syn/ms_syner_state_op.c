/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_syner_state_op.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 04:20:01 by nmathieu          #+#    #+#             */
/*   Updated: 2022/06/17 10:31:13 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms/parse/syn.h"
#include "ms/parse/syner.h"
#include "ms/parse/token.h"
#include "./ms_syner_absorbe.h"

static t_ms_syn_r	basic_op(
						t_ms_syner *self,
						t_ms_tok *tok,
						t_ms_syn *result,
						t_ms_syn_kind kind)
{
	if (tok->kind == MS_TOK_NEWLINE)
		return (MS_SYN_R_INCOMPLETE);
	if (tok->kind == MS_TOK_EOF)
		return (MS_SYN_R_UNEXPECTED_TOKEN);
	result->kind = kind;
	self->state = MS_SYNER_INIT;
	return (MS_SYN_R_SUCCESS_PRESERVE);
}

t_ms_syn_r	ms_syner_state_and_if(
				t_ms_syner *self,
				t_ms_tok *token,
				t_ms_syn *result)
{
	return (basic_op(self, token, result, MS_SYN_AND_IF));
}

t_ms_syn_r	ms_syner_state_or_if(
				t_ms_syner *self,
				t_ms_tok *token,
				t_ms_syn *result)
{
	return (basic_op(self, token, result, MS_SYN_OR_IF));
}

t_ms_syn_r	ms_syner_state_pipe(
				t_ms_syner *self,
				t_ms_tok *token,
				t_ms_syn *result)
{
	return (basic_op(self, token, result, MS_SYN_PIPE));
}

t_ms_syn_r	ms_syner_state_seq(
				t_ms_syner *self,
				t_ms_tok *token,
				t_ms_syn *result)
{
	if (token->kind == MS_TOK_NEWLINE)
		return (MS_SYN_R_INCOMPLETE);
	if (token->kind == MS_TOK_CPAREN)
	{
		self->state = MS_SYNER_CPAREN;
		return (MS_SYN_R_INCOMPLETE);
	}
	result->kind = MS_SYN_SEQ;
	self->state = MS_SYNER_INIT;
	return (MS_SYN_R_SUCCESS_PRESERVE);
}
