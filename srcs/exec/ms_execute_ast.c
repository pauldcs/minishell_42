/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execute_ast.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 16:35:16 by nmathieu          #+#    #+#             */
/*   Updated: 2022/07/28 11:39:13 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms/parse/ast.h"
#include "ms/parse/expand.h"
#include "ms/state.h"
#include "ms/utils/debug.h"
#include "ms/utils/io.h"
#include "ms/exec/ms_execute.h"
#include "ms/exec/ms_general.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

bool	ms_execute_expast(t_ms_expast *ast)
{
	if (ast->kind == MS_AST_CMD)
		ms_simple_command(ast);
	else if (ast->kind == MS_AST_SUBSH)
		ms_setup_subsh(ast);
	else if (ast->kind == MS_AST_PIPE)
		ms_pipeline(ast);
	else if (ast->kind == MS_AST_OR_IF)
		ms_or_if(ast);
	else if (ast->kind == MS_AST_AND_IF)
		ms_and_if(ast);
	else if (ast->kind == MS_AST_SEQ)
		ms_seq(ast);
	return (true);
}

bool	ms_execute_ast(t_ms_ast *ast)
{
	t_ms_expast	expast;

	if (!ast)
	{
		g_ms.status = 0;
		return (true);
	}
	if (!ms_expast_init(&expast, ast))
	{
		g_ms.status = 1;
		return (false);
	}
	ms_execute_expast(&expast);
	ms_expast_deinit(&expast);
	return (true);
}
