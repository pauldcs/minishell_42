/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_setup_subsh.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pducos <pducos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 15:52:22 by pducos            #+#    #+#             */
/*   Updated: 2022/07/07 19:42:07 by pducos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "ms/state.h"
#include "ms/parse/expand.h"
#include "ms/exec/ms_general.h"
#include "ms/utils/io.h"
#include "ms/exec.h"
#include "ms/exec/ms_redir.h"
#include <sys/wait.h>

void	ms_setup_subsh(t_ms_expast *ast)
{
	pid_t	id;
	int		stat;

	id = fork();
	if (id == -1)
	{
		ms_error("%s: fork failed\n", g_ms.exec_name);
		return ;
	}
	else if (id == 0)
	{
		if (ms_do_redirections(
				ast->cmd.iords,
				ast->cmd.iord_count) == EXIT_SUCCESS)
			ms_execute_ast(ast->subsh.root);
		ms_fri_and_exit(g_ms.status);
	}
	waitpid(id, &stat, 0);
	g_ms.status = WEXITSTATUS(stat);
}
