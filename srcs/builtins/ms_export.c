/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 09:54:09 by nmathieu          #+#    #+#             */
/*   Updated: 2022/07/26 11:45:45 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms/state.h"
#include "ms/utils/io.h"

static void	ms_show_exported(void)
{
	size_t	i;

	i = 0;
	while (i < g_ms.vars.len)
	{
		if (g_ms.vars.buf[i].exported)
		{
			ms_putstr("export ");
			ms_putstr(g_ms.vars.buf[i].name);
			if (g_ms.vars.buf[i].value)
			{
				ms_putstr("=\"");
				ms_putstr(g_ms.vars.buf[i].value);
				ms_putstr("\"\n");
			}
			else
				ms_putstr("\n");
		}
		i++;
	}
}

static bool	is_ident(char *s)
{
	if (('A' > *s || *s > 'Z') && ('a' > *s || *s > 'z') && *s != '_')
		return (false);
	s++;
	while (('A' <= *s && *s <= 'Z') || ('a' <= *s && *s <= 'z') || *s == '_'
		|| ('0' <= *s && *s <= '9'))
		s++;
	return (!*s);
}

static void	process_var(char *var)
{
	int			ret;
	t_ms_assign	assign;

	ret = ms_assign_parse(&assign, var);
	if (ret == 0)
	{
		if (is_ident(var))
			ms_var_set(&g_ms.vars, ms_str_dup(var), NULL, true);
		else
			ms_error("%s: export: '%s': not a valid identifier\n",
				g_ms.exec_name, var);
	}
	else if (ret == 1)
		ms_var_assign(&g_ms.vars, assign, true);
}

int	ms_export(char **args, char **envp)
{
	size_t		i;

	(void)envp;
	if (!args[1])
	{
		ms_show_exported();
		return (0);
	}
	i = 1;
	while (args[i])
		process_var(args[i++]);
	return (0);
}
