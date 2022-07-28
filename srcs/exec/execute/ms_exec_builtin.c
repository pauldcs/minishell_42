/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 11:58:19 by pducos            #+#    #+#             */
/*   Updated: 2022/07/26 11:48:41 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms/state.h"
#include "ms/exec/ms_builtins.h"
#include "ms/parse/expand.h"
#include "ms/utils/io.h"
#include <stdlib.h>

static void	free_2d(char **p)
{
	size_t	i;

	i = 0;
	while (p[i])
		free(p[i++]);
	free(p);
}

#define BUILTIN_COUNT 7

static const char *const	g_builtins_names[BUILTIN_COUNT] = {
	"cd",
	"pwd",
	"exit",
	"env",
	"unset",
	"echo",
	"export",
};

static int					(*g_builtins[BUILTIN_COUNT])(char **a, char **e) = {
	ms_cd,
	ms_pwd,
	ms_exit,
	ms_env,
	ms_unset,
	ms_echo,
	ms_export,
};

bool	ms_is_builtin(const char *name)
{
	size_t	i;

	i = 0;
	while (i < BUILTIN_COUNT)
	{
		if (ms_str_cmp(g_builtins_names[i], name) == 0)
			return (true);
		i++;
	}
	return (false);
}

void	ms_exec_builtin(t_ms_expast *ast)
{
	char	**envp;
	size_t	i;

	envp = ms_var_env(&g_ms.vars, ast->cmd.overrides, &ast->cmd.override_count);
	if (!envp)
		return ;
	i = 0;
	while (i < BUILTIN_COUNT)
	{
		if (ms_str_cmp(g_builtins_names[i], ast->cmd.args[0]) == 0)
		{
			g_ms.status = g_builtins[i](ast->cmd.args, envp);
			break ;
		}
		i++;
	}
	if (i == BUILTIN_COUNT)
		ms_error("%s: %s: Not implemented\n", g_ms.exec_name, ast->cmd.args[0]);
	free_2d(envp);
}
