/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipeline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pducos <pducos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 18:30:10 by pducos            #+#    #+#             */
/*   Updated: 2022/07/18 15:26:22 by pducos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms/parse/ast.h"
#include "ms/parse/expand.h"
#include "ms/exec/ms_general.h"
#include "ms/state.h"
#include "ms/exec.h"
#include "ms/utils/io.h"
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
/*
static int	__exec(t_ms_ast *ast, int sv, int p_in, int p_out)
{
	char	*name;
	char	**args;
	pid_t	id;

	args = NULL;
	if (ast->kind != MS_AST_CMD)
		name = NULL;
	else
	{
		args = ms_expand_args(ast->cmd.args, ast->cmd.arg_count);
			if (!args)
		return (EXIT_FAILURE);
		name = ms_find_cmd(*args);
	}
	id = fork();
	if (id == 0)
	{
		do_pipe(sv, p_in);
		ms_close_fd(&p_out);
		if (ms_do_redirections(ast->cmd.iords,
				ast->cmd.iord_count) == EXIT_FAILURE)
			exit(126);
		if (ast->kind == MS_AST_PIPE
			|| ast->kind == MS_AST_AND_IF
			|| ast->kind == MS_AST_OR_IF
			|| ast->kind == MS_AST_SUBSH)
		{
			ms_execute_ast(ast);
			if (name)
				free(name);
			if (args)
				ms_free_array(args);
			exit(EXIT_SUCCESS);
		}
		if (!name)
			exit(127);
		execve(name, args, NULL);
		ms_error("%s: %d: execve failed\n", __FILE__, __LINE__);
		free(name);
		exit(EXIT_FAILURE);
	}
	__id = id;
	if (name)
		free(name);
	if (args)
		ms_free_array(args);
	ms_close_fd(&p_in);
	if (ast->kind == MS_AST_CMD)
		ms_close_fd(&sv);
	return (p_out);
}

int	ms_pipe_no_fork(t_ms_ast *ast)
{
	int			p[2];
	static int	sv;
	int			ret;

	while (ast)
	{
		if (ast->kind == MS_AST_PIPE)
		{
			if (pipe(p) == -1)
			{
				ms_error("%s: %d: pipe failed\n", __FILE__, __LINE__);
				return (EXIT_FAILURE);
			}
			sv = __exec(ast->binop.left, sv, p[1], p[0]);
		}
		else
		{
			sv = __exec(ast, sv, SKIP, SKIP);
			break ;
		}
		ast = ast->binop.right;
	}
	waitpid(__id, &ret, 0);
	while (waitpid(0, 0, 0) != -1);
	ms_close_fd(&sv);
	return (return_value(ret));
}
*/

int	do_fork(t_ms_ast *ast, int clone, int original, int to_close)
{
	pid_t	id;

	id = fork();
	if (id == -1)
		return (ms_error(
				"%s: fork failed\n", g_ms.exec_name),
			-1);
	if (id == 0)
	{
		ms_sigset_default();
		if (dup2(original, clone) == -1)
		{
			ms_error("%s: dup2 failed\n", g_ms.exec_name);
			exit(EXIT_FAILURE);
		}
		ms_close_fd(&to_close);
		ms_close_fd(&original);
		ms_execute_ast(ast);
		ms_fri_and_exit(g_ms.status);
	}
	return (id);
}

int	ms_do_piping(t_ms_expast *ast)
{
	int		stat;
	int		p[2];
	pid_t	pids[2];

	if (pipe(p) == -1)
		return (ms_error("%s: pipe failed\n", g_ms.exec_name), EXIT_FAILURE);
	pids[0] = do_fork(ast->binop.left, STDOUT_FILENO, p[1], p[0]);
	close(p[1]);
	pids[1] = do_fork(ast->binop.right, STDIN_FILENO, p[0], -1);
	waitpid(pids[1], &stat, 0);
	close(p[0]);
	waitpid(pids[0], 0, 0);
	if (WIFSIGNALED(stat))
		return (ms_put_sig(WTERMSIG(stat)), 128 + WTERMSIG(stat));
	else
		return (WEXITSTATUS(stat));
}

void	ms_pipeline(t_ms_expast *ast)
{
	g_ms.status = ms_do_piping(ast);
}
