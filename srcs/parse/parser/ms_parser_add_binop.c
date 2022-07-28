/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser_add_binop.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 11:11:28 by nmathieu          #+#    #+#             */
/*   Updated: 2022/06/30 09:57:47 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms/parse/parser.h"
#include "ms/parse/ast.h"
#include "ms/utils/debug.h"
#include "./ms_parser_absorbe.h"

static bool	ms_perform_parent_swap(t_ms_ast **to_replace, t_ms_ast_kind kind)
{
	t_ms_ast	*tmp;
	t_ms_ast	*binop;

	binop = ms_ast_create_binop(kind);
	if (!binop)
		return (false);
	tmp = *to_replace;
	*to_replace = binop;
	(*to_replace)->binop.left = tmp;
	return (true);
}

bool	ms_parser_add_binop(t_ms_parser *self, t_ms_ast_kind kind)
{
	t_ms_ast	**pos;

	pos = ms_parser_get_op_pos(self, kind);
	if (!ms_perform_parent_swap(pos, kind)
		|| !ms_parser_push_scope(self, &(*pos)->binop.right))
		return (false);
	return (true);
}
