/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_ast_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 11:25:06 by nmathieu          #+#    #+#             */
/*   Updated: 2022/07/08 13:01:09 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms/parse/ast.h"
#include "ms/utils/alloc.h"
#include "ms/utils/mem.h"

t_ms_ast	*ms_ast_create_cmd(t_ms_command *cmd)
{
	t_ms_ast	*ret;

	ret = ms_alloc(sizeof(t_ms_ast));
	if (!ret)
		return (NULL);
	ret->kind = MS_AST_CMD;
	ms_mem_copy(&ret->cmd, cmd, sizeof(t_ms_command));
	return (ret);
}

t_ms_ast	*ms_ast_create_binop(t_ms_ast_kind kind)
{
	t_ms_ast	*ret;

	ret = ms_alloc(sizeof(t_ms_ast));
	if (!ret)
		return (NULL);
	ret->kind = kind;
	ret->binop.left = NULL;
	ret->binop.right = NULL;
	return (ret);
}

t_ms_ast	*ms_ast_create_subsh(void)
{
	t_ms_ast	*ret;

	ret = ms_alloc(sizeof(t_ms_ast));
	if (!ret)
		return (NULL);
	ret->kind = MS_AST_SUBSH;
	ret->subsh.root = NULL;
	ret->subsh.iords = NULL;
	ret->subsh.iord_count = 0;
	return (ret);
}
