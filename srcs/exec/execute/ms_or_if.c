/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_or_if.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 14:12:16 by pducos            #+#    #+#             */
/*   Updated: 2022/07/08 12:00:23 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms/state.h"
#include "ms/parse/expand.h"
#include "ms/exec.h"

void	ms_or_if(t_ms_expast *ast)
{
	ms_execute_ast(ast->binop.left);
	if (g_ms.status && !g_ms.exit_called)
		ms_execute_ast(ast->binop.right);
}
