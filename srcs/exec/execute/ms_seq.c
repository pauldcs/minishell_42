/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_seq.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 21:11:11 by pducos            #+#    #+#             */
/*   Updated: 2022/07/08 12:04:51 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms/parse/ast.h"
#include "ms/parse/expand.h"
#include "ms/exec.h"

void	ms_seq(t_ms_expast *ast)
{
	ms_execute_ast(ast->binop.left);
	if (!g_ms.exit_called)
		ms_execute_ast(ast->binop.right);
}
