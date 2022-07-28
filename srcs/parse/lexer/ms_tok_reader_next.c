/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tok_reader_next.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 12:53:14 by nmathieu          #+#    #+#             */
/*   Updated: 2022/06/11 14:44:33 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms/parse/tok_reader.h"
#include "ms/parse/lexer.h"

#include <unistd.h>

static bool	ms_fill_buffer(t_ms_tok_reader *self)
{
	ssize_t	count;

	count = read(self->fd, self->buf, MS_TOK_READER_BUF_SIZE);
	if (count < 0)
		return (false);
	else if (count == 0)
	{
		self->init = 1;
		self->buf[0] = '\0';
	}
	else
		self->init = count;
	self->cur = 0;
	return (true);
}

int	ms_tok_reader_next(t_ms_tok_reader *self, t_ms_tok *token)
{
	int	ret;

	if (self->exhausted)
		return (0);
	while (true)
	{
		if (self->cur == self->init && !ms_fill_buffer(self))
			return (-1);
		if (self->buf[self->cur] == '\n')
			self->line++;
		ret = ms_lexer_absorbe(&self->lexer, self->buf[self->cur], token);
		if (ret == MS_LEX_R_FAILURE)
			return (-1);
		if (ret == MS_LEX_R_SUCCESS_SAME || ret == MS_LEX_R_SUCCESS_ANOTHER)
		{
			if (token->kind & MS_TOK_ERR_MASK || token->kind == MS_TOK_EOF)
				self->exhausted = true;
			if (ret == MS_LEX_R_SUCCESS_ANOTHER)
				self->cur++;
			return (1);
		}
		self->cur++;
	}
}
