/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer_absorbe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 15:37:14 by nmathieu          #+#    #+#             */
/*   Updated: 2022/07/04 12:12:11 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ms_lexer_absorbe.h"
#include "./chars/ms_chars.h"
#include "ms/utils/mem.h"
#include "ms/utils/alloc.h"
#include "ms/utils/io.h"
#include "ms/utils/debug.h"

#include <stdlib.h>
#include <stdint.h>

static const t_ms_lex_trans	g_init_table[] = {
{ms_isnull, MS_LEX_EOF_F},
{ms_isoparen, MS_LEX_OPAREN_F},
{ms_iscparen, MS_LEX_CPAREN_F},
{ms_issquote, MS_LEX_SQUOTE},
{ms_isdquote, MS_LEX_DQUOTE},
{ms_isand, MS_LEX_AND},
{ms_isor, MS_LEX_OR},
{ms_isless, MS_LEX_LESS},
{ms_isgreat, MS_LEX_GREAT},
{ms_iseol, MS_LEX_NEWLINE_F},
{ms_isspace, MS_LEX_INIT},
{ms_ischar, MS_LEX_WORD},
};

static const t_ms_lex_trans	g_word_table[] = {
{ms_isspace, MS_LEX_WORD_F},
{ms_ispunct, MS_LEX_WORD_F},
{ms_issquote, MS_LEX_SQUOTE},
{ms_isdquote, MS_LEX_DQUOTE},
{ms_ischar, MS_LEX_WORD},
};

static const t_ms_lex_trans	g_squote_table[] = {
{ms_issquote, MS_LEX_WORD},
{ms_isnull, MS_LEX_ERR_NOSQUOTE},
{ms_ischar, MS_LEX_SQUOTE},
};

static const t_ms_lex_trans	g_dquote_table[] = {
{ms_isdquote, MS_LEX_WORD},
{ms_isnull, MS_LEX_ERR_NODQUOTE},
{ms_ischar, MS_LEX_DQUOTE},
};

static const t_ms_lex_trans	g_and_table[] = {
{ms_isand, MS_LEX_DAND_F},
{ms_ispunct, MS_LEX_WORD_F},
{ms_isspace, MS_LEX_WORD_F},
{ms_ischar, MS_LEX_WORD},
};

static const t_ms_lex_trans	g_or_table[] = {
{ms_isor, MS_LEX_DOR_F},
{ms_ischar, MS_LEX_OR_F},
};

static const t_ms_lex_trans	g_less_table[] = {
{ms_isless, MS_LEX_DLESS_F},
{ms_ischar, MS_LEX_LESS_F},
};

static const t_ms_lex_trans	g_dless_table[] = {
{ms_ischar, MS_LEX_DLESS_F},
};

static const t_ms_lex_trans	g_great_table[] = {
{ms_isgreat, MS_LEX_DGREAT_F},
{ms_ischar, MS_LEX_GREAT_F},
};

static const t_ms_lex_trans	*g_trans_tables[] = {
	g_init_table,
	g_word_table,
	g_squote_table,
	g_dquote_table,
	g_and_table,
	g_or_table,
	g_great_table,
	g_less_table,
	g_dless_table,
};

static const t_ms_lex_final	g_finals[] = {
{MS_TOK_EOF, MS_LEX_R_SUCCESS_ANOTHER},
{MS_TOK_NEWLINE, MS_LEX_R_SUCCESS_ANOTHER},
{MS_TOK_WORD, MS_LEX_R_SUCCESS_SAME},
{MS_TOK_DAND, MS_LEX_R_SUCCESS_ANOTHER},
{MS_TOK_OR, MS_LEX_R_SUCCESS_SAME},
{MS_TOK_DOR, MS_LEX_R_SUCCESS_ANOTHER},
{MS_TOK_LESS, MS_LEX_R_SUCCESS_SAME},
{MS_TOK_DLESS, MS_LEX_R_SUCCESS_ANOTHER},
{MS_TOK_GREAT, MS_LEX_R_SUCCESS_SAME},
{MS_TOK_DGREAT, MS_LEX_R_SUCCESS_ANOTHER},
{MS_TOK_OPAREN, MS_LEX_R_SUCCESS_ANOTHER},
{MS_TOK_CPAREN, MS_LEX_R_SUCCESS_ANOTHER},
{MS_TOK_ERR_NOSQUOTE, MS_LEX_R_SUCCESS_SAME},
{MS_TOK_ERR_NODQUOTE, MS_LEX_R_SUCCESS_SAME},
};

static t_ms_lex_state	ms_get_next_state(
								const t_ms_lex_trans *table,
								char c)
{
	size_t	i;

	i = 0;
	while (true)
	{
		if ((table[i].charclass)(c))
			return (table[i].state);
		i++;
	}
}

static bool	push_char(t_ms_lexer *self, char c)
{
	if (!ms_vec_reserve((t_ms_vec *)&self->chars, 1, sizeof(char)))
		return (false);
	self->chars.buf[self->chars.len] = c;
	self->chars.len++;
	return (true);
}

t_ms_lex_r	ms_lexer_absorbe(t_ms_lexer *self, char c, t_ms_tok *res)
{
	size_t	final_index;

	self->state = ms_get_next_state(g_trans_tables[self->state], c);
	if ((self->state & MS_LEX_TOK_MASK) == 0)
	{
		ms_assert(c != '\0', "unhandled '\\0'");
		if (self->state != MS_LEX_INIT && !push_char(self, c))
			return (MS_LEX_R_FAILURE);
		return (MS_LEX_R_INCOMPLETE);
	}
	final_index = self->state & ~MS_LEX_TOK_MASK;
	res->kind = g_finals[final_index].kind;
	if (g_finals[final_index].ret == MS_LEX_R_SUCCESS_ANOTHER)
	{
		if (self->chars.len == self->chars.cap
			&& !ms_vec_reserve((t_ms_vec *)&self->chars, 1, sizeof(char)))
			return (MS_LEX_R_FAILURE);
		self->chars.buf[self->chars.len++] = c;
	}
	if (!push_char(self, '\0'))
		return (false);
	res->slice = self->chars.buf;
	self->state = MS_LEX_INIT;
	self->chars.len = 0;
	return (g_finals[final_index].ret);
}
