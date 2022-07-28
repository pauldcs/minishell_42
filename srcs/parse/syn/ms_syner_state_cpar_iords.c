/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_syner_state_cpar_iords.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 23:08:06 by nmathieu          #+#    #+#             */
/*   Updated: 2022/06/27 21:01:10 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms/parse/syner.h"
#include "ms/parse/token.h"
#include "ms/parse/syn.h"
#include "./ms_syner_absorbe.h"

static t_ms_syn_r	ms_syner_state_cpar_basic(
						t_ms_syner *self,
						t_ms_tok *token,
						t_ms_syn *result,
						t_ms_iord_kind kind)
{
	(void)result;
	if (token->kind != MS_TOK_WORD)
		return (MS_SYN_R_UNEXPECTED_TOKEN);
	if (!ms_syner_parse_basic_iord(self, kind, token->slice))
		return (MS_SYN_R_FAILURE);
	self->state = MS_SYNER_CPAREN;
	return (MS_SYN_R_INCOMPLETE);
}

t_ms_syn_r	ms_syner_state_cpar_write(
				t_ms_syner *self,
				t_ms_tok *token,
				t_ms_syn *result)
{
	return (ms_syner_state_cpar_basic(self, token, result, MS_IORD_WRITE));
}

t_ms_syn_r	ms_syner_state_cpar_append(
				t_ms_syner *self,
				t_ms_tok *token,
				t_ms_syn *result)
{
	return (ms_syner_state_cpar_basic(self, token, result, MS_IORD_APPEND));
}

t_ms_syn_r	ms_syner_state_cpar_read(
				t_ms_syner *self,
				t_ms_tok *token,
				t_ms_syn *result)
{
	return (ms_syner_state_cpar_basic(self, token, result, MS_IORD_READ));
}

t_ms_syn_r	ms_syner_state_cpar_here_doc(
				t_ms_syner *self,
				t_ms_tok *token,
				t_ms_syn *result)
{
	(void)result;
	if (token->kind != MS_TOK_WORD)
		return (MS_SYN_R_UNEXPECTED_TOKEN);
	if (!ms_syner_parse_here_doc(self, token->slice))
		return (MS_SYN_R_FAILURE);
	self->state = MS_SYNER_CPAREN;
	return (MS_SYN_R_INCOMPLETE);
}
