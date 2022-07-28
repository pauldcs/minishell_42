/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_syner_state_init.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 23:08:06 by nmathieu          #+#    #+#             */
/*   Updated: 2022/07/04 17:10:35 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms/parse/syner.h"
#include "ms/parse/token.h"
#include "ms/parse/syn.h"
#include "ms/parse/expand.h"
#include "ms/utils/alloc.h"
#include "./ms_syner_absorbe.h"

t_ms_syn_r	ms_syner_state_init(
				t_ms_syner *self,
				t_ms_tok *token,
				t_ms_syn *result)
{
	if (token->kind == MS_TOK_GREAT)
		self->state = MS_SYNER_CMD_WRITE;
	else if (token->kind == MS_TOK_DGREAT)
		self->state = MS_SYNER_CMD_APPEND;
	else if (token->kind == MS_TOK_LESS)
		self->state = MS_SYNER_CMD_READ;
	else if (token->kind == MS_TOK_DLESS)
		self->state = MS_SYNER_CMD_HERE_DOC;
	else if (token->kind == MS_TOK_WORD)
	{
		self->state = MS_SYNER_COMMAND;
		return (ms_syner_append_word(self, token->slice));
	}
	else if (token->kind == MS_TOK_OPAREN)
		self->state = MS_SYNER_OPAREN;
	else if ((token->kind == MS_TOK_NEWLINE || token->kind == MS_TOK_EOF)
		&& self->depth == 0)
	{
		result->kind = MS_SYN_END;
		return (MS_SYN_R_SUCCESS_CONSUME);
	}
	else
		return (MS_SYN_R_UNEXPECTED_TOKEN);
	return (MS_SYN_R_INCOMPLETE);
}
