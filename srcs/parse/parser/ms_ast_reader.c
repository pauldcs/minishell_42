/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_ast_reader.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 17:56:35 by nmathieu          #+#    #+#             */
/*   Updated: 2022/06/10 21:44:11 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms/parse/ast_reader.h"
#include "ms/parse/tok_reader.h"
#include <stdbool.h>

bool	ms_ast_reader_init(t_ms_ast_reader *self, int fd)
{
	self->exhausted = false;
	if (!ms_parser_init(&self->parser))
		return (false);
	ms_syn_reader_init(&self->syn_reader, fd);
	return (true);
}

void	ms_ast_reader_deinit(t_ms_ast_reader *self)
{
	ms_syn_reader_deinit(&self->syn_reader);
	ms_parser_deinit(&self->parser);
}
