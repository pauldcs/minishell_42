/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 15:15:40 by pducos            #+#    #+#             */
/*   Updated: 2022/07/26 11:45:11 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "ms/utils/io.h"
#include "ms/state.h"
#include "ms/exec/ms_general.h"

char	*__cwd(void)
{
	char		*dir;
	static char	dirbuf[PATH_MAX];

	dir = getcwd(dirbuf, sizeof(dirbuf));
	if (!dir)
		return (NULL);
	return (dir);
}

static bool	is_absolute(char *str)
{
	if (str == NULL || *str == 0)
		return (false);
	if (*str == '/')
		return (true);
	if (*str == '.')
	{
		str++;
		if (!*str
			|| *str == '/'
			|| (*str == '.' && (*(str + 1) == '\0'
					|| *(str + 1) == '/')))
			return (true);
	}
	return (false);
}

static char	*create_absolute(char *path)
{
	char	*buf;
	char	*cwd;

	cwd = __cwd();
	if (cwd)
	{
		buf = malloc(
				ms_strs_len(3,
					cwd, "/", path)
				+ 1);
		if (buf)
		{
			*buf = '\0';
			ms_str_cat(buf, cwd);
			ms_str_cat(buf, "/");
			ms_str_cat(buf, path);
			return (buf);
		}
	}
	return (NULL);
}

static char	*move_to_directory(char *path, char *dir)
{
	if (ms_file_exists(path))
	{
		if (!ms_file_is_directory(path))
			return (
				ms_error("%s: cd: %s: Not a directory\n", g_ms.exec_name, dir),
				NULL);
		if (chdir(path) == -1)
			return (ms_error("%s: cd: %s: %s\n", g_ms.exec_name,
					dir, strerror(errno)),
				NULL);
		return (__cwd());
	}
	ms_error("%s: cd: %s: No such file or directory\n", g_ms.exec_name, dir);
	return (NULL);
}

int	ms_cd(char **args, char **envp)
{
	char	*dir;
	char	*dest;

	(void)envp;
	if (!args[1])
	{
		dir = ms_save_str(ms_var_get(&g_ms.vars, (t_ms_str){"HOME", 4}));
		if (!dir)
			return (ms_error("%s: cd: HOME not set\n", g_ms.exec_name), 1);
	}
	else if (args[2])
		return (ms_error("%s: cd: too many arguments\n", g_ms.exec_name), 1);
	else if (is_absolute(args[1]))
		dir = ms_save_str(args[1]);
	else
		dir = create_absolute(args[1]);
	if (!dir)
		return (EXIT_FAILURE);
	dest = move_to_directory(dir, args[1]);
	if (!dest
		|| !ms_var_setup(&g_ms.vars, "OLDPWD",
			ms_var_get(&g_ms.vars, (t_ms_str){"PWD", 3}), false)
		|| !ms_var_setup(&g_ms.vars, "PWD", dest, false))
		return (free(dir), EXIT_FAILURE);
	return (free(dir), EXIT_SUCCESS);
}
