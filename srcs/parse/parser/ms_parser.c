/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 00:00:26 by nmathieu          #+#    #+#             */
/*   Updated: 2022/06/30 11:15:33 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms/parse/parser.h"
#include "ms/parse/lexer.h"
#include "ms/utils/mem.h"
#include "./ms_parser_absorbe.h"
#include <stddef.h>
#include <stdlib.h>

bool	ms_parser_init(t_ms_parser *self)
{
	ms_mem_set(self, 0x00, sizeof(t_ms_parser));
	if (!ms_parser_push_scope(self, &self->result))
		return (false);
	return (true);
}

void	ms_parser_deinit(t_ms_parser *self)
{
	ms_ast_free(self->result);
	if (self->scopes.cap)
		free(self->scopes.buf);
	if (self->parens.cap)
		free(self->parens.buf);
}
