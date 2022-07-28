/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser_get_op_pos.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 09:55:13 by nmathieu          #+#    #+#             */
/*   Updated: 2022/06/30 11:23:28 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms/parse/parser.h"
#include "ms/parse/ast.h"
#include "./ms_parser_absorbe.h"
#include "ms/utils/debug.h"

t_ms_ast	**ms_parser_get_op_pos(t_ms_parser *self, t_ms_ast_kind kind)
{
	size_t	i;
	int		prec;

	prec = ms_ast_precedence(kind);
	ms_assert(self->scopes.len, "scope is empty?");
	i = self->scopes.len - 1;
	while (i)
	{
		if (ms_ast_precedence((*self->scopes.buf[i - 1])->kind) > prec)
			break ;
		i--;
	}
	self->scopes.len = i + 1;
	return (self->scopes.buf[i]);
}
