/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_find_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 10:19:36 by pducos            #+#    #+#             */
/*   Updated: 2022/07/12 14:02:25 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ms/utils/str.h"
#include "ms/utils/mem.h"
#include "ms/utils/io.h"
#include "ms/state.h"
#include "ms/exec/ms_general.h"

static char	**split_paths(void)
{
	const char	*env;

	env = ms_var_get(&g_ms.vars, (t_ms_str){"PATH", 4});
	if (env)
		return (ms_str_split(env, ':'));
	return (NULL);
}

static char	*ms_find_user_command(char *filename)
{
	char			**paths;
	char			*path;
	register int	idx;

	idx = 0;
	paths = split_paths();
	if (!paths)
		return (NULL);
	while (paths[idx])
	{
		path = malloc(ms_strs_len(3, paths[idx], "/", filename) + 1);
		if (!path)
			return (ms_free_array(paths), NULL);
		path[0] = 0x00;
		ms_str_cat(path, paths[idx++]);
		ms_str_cat(path, "/");
		ms_str_cat(path, filename);
		if (ms_file_exists(path))
			break ;
		else
			ms_mem_free(&path);
	}
	return (ms_free_array(paths), path);
}

char	*ms_find_cmd(char *name)
{
	char	*path;

	if (!name)
		return (NULL);
	if (ms_str_chr(name, '/'))
	{
		if (ms_file_exists(name))
			return (ms_save_str(name));
		ms_error("%s: %s: No such file or directory\n", g_ms.exec_name, name);
		return (NULL);
	}
	else if (*name)
	{
		path = ms_find_user_command(name);
		if (path)
			return (path);
	}
	ms_error("%s: %s: command not found\n", g_ms.exec_name, name);
	return (NULL);
}
