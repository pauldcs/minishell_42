/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_syner_state_paren.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 23:51:26 by nmathieu          #+#    #+#             */
/*   Updated: 2022/06/27 21:00:55 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms/parse/syner.h"
#include "ms/parse/token.h"
#include "ms/parse/syn.h"
#include "ms/utils/alloc.h"
#include "./ms_syner_absorbe.h"

static void	finish_cparen(t_ms_syner *self, t_ms_syn *result)
{
	result->kind = MS_SYN_CPAREN;
	result->cparen.iord_count = self->iords.len;
	result->cparen.iords = self->iords.buf;
	self->iords.len = 0;
	self->iords.cap = 0;
}

t_ms_syn_r	ms_syner_state_cparen(
				t_ms_syner *self,
				t_ms_tok *token,
				t_ms_syn *result)
{
	if (token->kind == MS_TOK_DLESS)
		self->state = MS_SYNER_CPAR_HERE_DOC;
	else if (token->kind == MS_TOK_LESS)
		self->state = MS_SYNER_CPAR_READ;
	else if (token->kind == MS_TOK_DGREAT)
		self->state = MS_SYNER_CPAR_APPEND;
	else if (token->kind == MS_TOK_GREAT)
		self->state = MS_SYNER_CPAR_WRITE;
	else
	{
		self->depth--;
		finish_cparen(self, result);
		self->state = MS_SYNER_COMMAND_END;
		return (MS_SYN_R_SUCCESS_PRESERVE);
	}
	return (MS_SYN_R_INCOMPLETE);
}

t_ms_syn_r	ms_syner_state_oparen(
				t_ms_syner *self,
				t_ms_tok *token,
				t_ms_syn *result)
{
	if (token->kind == MS_TOK_NEWLINE)
		return (MS_SYN_R_INCOMPLETE);
	result->kind = MS_SYN_OPAREN;
	self->depth++;
	self->state = MS_SYNER_INIT;
	return (MS_SYN_R_SUCCESS_PRESERVE);
}
