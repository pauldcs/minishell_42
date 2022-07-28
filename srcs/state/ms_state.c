/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_state.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:27:54 by nmathieu          #+#    #+#             */
/*   Updated: 2022/07/26 11:30:38 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms/state.h"
#include "ms/utils/io.h"
#include "ms/utils/mem.h"
#include "ms/utils/str.h"
#include <stdlib.h>
#include <unistd.h>

bool	ms_setup_vars(void);

t_ms_state	g_ms;

static const char	*basename(const char *path)
{
	const char	*basename;

	basename = path;
	while (*path)
	{
		if (*path == '/')
			basename = path + 1;
		path++;
	}
	return (basename);
}

bool	ms_init_state(const char *exec_name, char **envp)
{
	ms_mem_set(&g_ms, 0x00, sizeof(t_ms_state));
	g_ms.exec_name = basename(exec_name);
	if (!ms_vars_parse(&g_ms.vars, envp) || !ms_setup_vars())
		return (false);
	ms_sigset_prompt();
	g_ms.stdin = dup(STDIN_FILENO);
	g_ms.stdout = dup(STDOUT_FILENO);
	g_ms.stderr = dup(STDERR_FILENO);
	if (g_ms.stdin == -1
		|| g_ms.stdout == -1
		|| g_ms.stderr == -1)
		return (false);
	return (true);
}

void	ms_deinit_state(void)
{
	while (g_ms.vars.len)
		ms_var_deinit(&g_ms.vars.buf[--g_ms.vars.len]);
	if (g_ms.vars.cap)
		free(g_ms.vars.buf);
	close(g_ms.stdin);
	close(g_ms.stdout);
	close(g_ms.stderr);
}
