/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_setup_vars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 10:46:29 by nmathieu          #+#    #+#             */
/*   Updated: 2022/07/28 11:39:30 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms/state.h"
#include "ms/utils/io.h"
#include "ms/utils/alloc.h"
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>

#define DFLT_PS1 "\1\e[31m\2darksasuke\1\e[39m\2$ \1\e[0m\2"
#define DFLT_PS2 "> "
#define DFLT_PATH "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"

static bool	ms_atoi(const char *s, int *ret)
{
	int	sign;

	sign = 1;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	if ('0' > *s || *s > '9')
		return (false);
	*ret = 0;
	while ('0' <= *s && *s <= '9')
	{
		if (*ret > (INT_MAX - (*s - '0')) / 10)
			return (false);
		*ret = *ret * 10 + (*s - '0');
		s++;
	}
	if (*s)
		return (false);
	*ret *= sign;
	return (true);
}

static size_t	num_len(int a)
{
	size_t	c;

	if (a == INT_MIN)
		return (11);
	if (a == 0)
		return (1);
	c = 0;
	if (a < 0)
	{
		a = -a;
		c++;
	}
	while (a)
	{
		c++;
		a /= 10;
	}
	return (c);
}

static char	*ms_itoa(int a)
{
	size_t	len;
	char	*ret;
	char	*cur;

	if (a == INT_MIN)
		return (ms_str_dup("-2147483648"));
	len = num_len(a);
	ret = ms_alloc(len + 1);
	if (!ret)
		return (NULL);
	ret[len] = '\0';
	cur = ret + len;
	if (a < 0)
	{
		a = -a;
		ret[0] = '-';
	}
	if (!a)
		*(--cur) = '0';
	while (a)
	{
		*(--cur) = (a % 10) + '0';
		a /= 10;
	}
	return (ret);
}

static bool	ms_setup_shlvl(void)
{
	const char	*lvl_str;
	int			lvl;
	char		*name;
	char		*new_lvl;

	lvl_str = ms_var_get(&g_ms.vars, (t_ms_str){"SHLVL", 5});
	if (!lvl_str || !ms_atoi(lvl_str, &lvl))
		return (ms_var_setup(&g_ms.vars, "SHLVL", "1", true));
	if (lvl < 0)
		return (ms_var_setup(&g_ms.vars, "SHLVL", "0", true));
	lvl++;
	if (lvl >= 1000)
	{
		ms_error("%s: warning: shell level (%d) too high, resetting to 1\n",
			g_ms.exec_name, lvl);
		return (ms_var_setup(&g_ms.vars, "SHLVL", "1", true));
	}
	new_lvl = ms_itoa(lvl);
	if (!new_lvl)
		return (false);
	name = ms_str_dup("SHLVL");
	if (!name)
		return (false);
	return (ms_var_set(&g_ms.vars, name, new_lvl, true));
}

bool	ms_setup_vars(void)
{
	char	*cwd;
	char	*pwd;

	if (false
		|| !ms_var_setup(&g_ms.vars, "PS1", DFLT_PS1, false)
		|| !ms_var_setup(&g_ms.vars, "PS2", DFLT_PS2, false)
		|| !ms_setup_shlvl())
		return (false);
	if (!ms_var_get(&g_ms.vars, (t_ms_str){"PATH", 4})
		&& !ms_var_setup(&g_ms.vars, "PATH", DFLT_PATH, false))
		return (false);
	if (!ms_var_setup(&g_ms.vars, "OLDPWD", NULL, true))
		return (false);
	pwd = ms_str_dup("PWD");
	if (!pwd)
		return (false);
	cwd = ms_alloc(PATH_MAX);
	if (!cwd || !getcwd(cwd, PATH_MAX))
		return (free(pwd), ms_error("%s: where am I? Is this heaven???\n",
				g_ms.exec_name), false);
	if (!ms_var_set(&g_ms.vars, pwd, cwd, true))
		return (free(pwd), false);
	return (true);
}
