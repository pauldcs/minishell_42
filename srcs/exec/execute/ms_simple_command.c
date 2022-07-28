/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_simple_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pducos <pducos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 19:36:34 by pducos            #+#    #+#             */
/*   Updated: 2022/07/28 11:19:15 by pducos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "ms/state.h"
#include "ms/exec/ms_execute.h"
#include "ms/exec/ms_redir.h"
#include "ms/utils/mem.h"
#include "ms/parse/expand.h"
#include "ms/utils/io.h"
#include "ms/exec/ms_general.h"

static int	__exec(t_ms_expast *ast, char *path)
{
	pid_t			id;
	static int		stat;
	char			**vars;

	vars = ms_var_env(&g_ms.vars, ast->cmd.overrides, &ast->cmd.override_count);
	if (!vars)
		return (1);
	id = fork();
	if (id < 0)
		return (f2d(vars), ms_error("%s: fork failed\n", g_ms.exec_name), -1);
	else if (id == 0)
	{
		ms_sigset_default();
		if (ms_do_redirections(
				ast->cmd.iords,
				ast->cmd.iord_count) == EXIT_SUCCESS)
			execve(path, ast->cmd.args, vars);
		ms_fri_and_exit(EXIT_FAILURE);
	}
	f2d(vars);
	waitpid(id, &stat, 0);
	if (WIFSIGNALED(stat))
		return (ms_put_sig(WTERMSIG(stat)),
			128 + WTERMSIG(stat));
	return (WEXITSTATUS(stat));
}

static void	set_vars(t_ms_assign *vars, size_t *count)
{
	size_t	i;

	i = 0;
	while (i < *count)
	{
		if (!ms_var_assign(&g_ms.vars, vars[i], false))
			break ;
		i++;
	}
	while (i < *count)
		ms_assign_free(&vars[i++]);
	if (*count)
		free(vars);
	*count = 0;
}

static int	handle_builtin(t_ms_expast *ast)
{
	if (ast->cmd.iord_count && ms_do_redirections(
			ast->cmd.iords,
			ast->cmd.iord_count) == EXIT_SUCCESS)
	{
		ms_exec_builtin(ast);
		if (dup2(g_ms.stdout, STDOUT_FILENO) == -1
			|| dup2(g_ms.stdin, STDIN_FILENO) == -1
			|| dup2(g_ms.stderr, STDERR_FILENO) == -1)
			return (ms_error("%s: dup2 failed\n", g_ms.exec_name),
				EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	ms_exec_builtin(ast);
	return (EXIT_SUCCESS);
}

static int	__empty_redirection(t_ms_expast *ast)
{
	if (ast->cmd.iord_count && ms_do_redirections(
			ast->cmd.iords,
			ast->cmd.iord_count) == EXIT_SUCCESS)
	{
		if (dup2(g_ms.stdout, STDOUT_FILENO) == -1
			|| dup2(g_ms.stdin, STDIN_FILENO) == -1
			|| dup2(g_ms.stderr, STDERR_FILENO) == -1)
			return (ms_error("%s: dup2 failed\n", g_ms.exec_name),
				EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

int	ms_simple_command(t_ms_expast *ast)
{
	char	*name;

	if (!ast->cmd.args[0])
		return (set_vars(ast->cmd.overrides, &ast->cmd.override_count),
			__empty_redirection(ast));
	if (ms_is_builtin(ast->cmd.args[0]) == true)
		return (handle_builtin(ast));
	name = ms_find_cmd(ast->cmd.args[0]);
	if (name)
	{
		g_ms.status = 126;
		if (ms_file_is_directory(name))
			return (ms_error("%s: %s: Is a directory\n", g_ms.exec_name, name),
				free(name), EXIT_FAILURE);
		if (!ms_file_is_execable(name))
			return (
				ms_error("%s: %s: Permission denied\n", g_ms.exec_name, name),
				free(name), EXIT_FAILURE);
		g_ms.status = __exec(ast, name);
		return (free(name), EXIT_FAILURE);
	}
	g_ms.status = 127;
	return (EXIT_SUCCESS);
}
