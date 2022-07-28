/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tok_reader.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 12:51:30 by nmathieu          #+#    #+#             */
/*   Updated: 2022/06/11 14:44:46 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms/parse/tok_reader.h"
#include "ms/parse/lexer.h"

void	ms_tok_reader_init(t_ms_tok_reader *reader, int fd)
{
	reader->fd = fd;
	reader->cur = 0;
	reader->init = 0;
	reader->exhausted = false;
	reader->line = 0;
	ms_lexer_init(&reader->lexer);
}

void	ms_tok_reader_deinit(t_ms_tok_reader *self)
{
	ms_lexer_deinit(&self->lexer);
}
