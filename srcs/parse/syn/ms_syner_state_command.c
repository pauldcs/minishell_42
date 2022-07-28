/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_syner_state_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 23:50:36 by nmathieu          #+#    #+#             */
/*   Updated: 2022/07/13 21:23:19 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms/parse/syner.h"
#include "ms/parse/token.h"
#include "ms/parse/syn.h"
#include "ms/parse/expand.h"
#include "ms/utils/alloc.h"
#include "ms/utils/mem.h"
#include "./ms_syner_absorbe.h"
#include <stdlib.h>

static int	absorbe_var(t_ms_syner *self, char *w)
{
	int	ret;

	if (!ms_vec_reserve((t_ms_vec *)&self->vars, 1, sizeof(t_ms_var)))
		return (-1);
	ret = ms_assign_parse(&self->vars.buf[self->vars.len], w);
	if (ret == -1 || ret == 0)
		return (ret);
	self->vars.len++;
	return (1);
}

t_ms_syn_r	ms_syner_append_word(t_ms_syner *self, char *word)
{
	int	ret;

	if (self->args.len == 0)
	{
		ret = absorbe_var(self, word);
		if (ret == -1)
			return (MS_SYN_R_FAILURE);
		if (ret == 1)
			return (MS_SYN_R_INCOMPLETE);
	}
	if (!ms_vec_reserve((t_ms_vec *)&self->args, 1, sizeof(char *)))
		return (MS_SYN_R_FAILURE);
	self->args.buf[self->args.len] = ms_str_dup(word);
	if (!self->args.buf[self->args.len])
		return (MS_SYN_R_FAILURE);
	self->args.len++;
	return (MS_SYN_R_INCOMPLETE);
}

static bool	finish_command(t_ms_syner *self, t_ms_syn *result)
{
	ms_mem_set(result, 0x00, sizeof(t_ms_syn));
	result->kind = MS_SYN_CMD;
	if (self->args.len)
	{
		result->cmd.args = self->args.buf;
		result->cmd.arg_count = self->args.len;
		self->args.len = 0;
		self->args.cap = 0;
	}
	if (self->iords.len)
	{
		result->cmd.iord_count = self->iords.len;
		result->cmd.iords = self->iords.buf;
		self->iords.len = 0;
		self->iords.cap = 0;
	}
	if (self->vars.len)
	{
		result->cmd.overrides = self->vars.buf;
		result->cmd.override_count = self->vars.len;
		self->vars.cap = 0;
		self->vars.len = 0;
	}
	return (true);
}

t_ms_syn_r	ms_syner_state_command(
				t_ms_syner *self,
				t_ms_tok *token,
				t_ms_syn *result)
{
	if (token->kind == MS_TOK_DLESS)
		self->state = MS_SYNER_CMD_HERE_DOC;
	else if (token->kind == MS_TOK_LESS)
		self->state = MS_SYNER_CMD_READ;
	else if (token->kind == MS_TOK_DGREAT)
		self->state = MS_SYNER_CMD_APPEND;
	else if (token->kind == MS_TOK_GREAT)
		self->state = MS_SYNER_CMD_WRITE;
	else if (token->kind == MS_TOK_WORD)
		return (ms_syner_append_word(self, token->slice));
	else
	{
		if (!finish_command(self, result))
			return (MS_SYN_R_FAILURE);
		self->state = MS_SYNER_COMMAND_END;
		return (MS_SYN_R_SUCCESS_PRESERVE);
	}
	return (MS_SYN_R_INCOMPLETE);
}

t_ms_syn_r	ms_syner_state_command_end(
				t_ms_syner *self,
				t_ms_tok *token,
				t_ms_syn *result)
{
	if (token->kind == MS_TOK_DAND)
		self->state = MS_SYNER_AND_IF;
	else if (token->kind == MS_TOK_DOR)
		self->state = MS_SYNER_OR_IF;
	else if (token->kind == MS_TOK_OR)
		self->state = MS_SYNER_PIPE;
	else if (token->kind == MS_TOK_NEWLINE && self->depth > 0)
		self->state = MS_SYNER_SEQ;
	else if (token->kind == MS_TOK_EOF && self->depth == 0)
	{
		result->kind = MS_SYN_END;
		self->state = MS_SYNER_INIT;
		return (MS_SYN_R_SUCCESS_PRESERVE);
	}
	else if (token->kind == MS_TOK_NEWLINE && self->depth == 0)
	{
		result->kind = MS_SYN_END;
		self->state = MS_SYNER_INIT;
		return (MS_SYN_R_SUCCESS_CONSUME);
	}
	else if (token->kind == MS_TOK_CPAREN && self->depth > 0)
		self->state = MS_SYNER_CPAREN;
	else
		return (MS_SYN_R_UNEXPECTED_TOKEN);
	return (MS_SYN_R_INCOMPLETE);
}
