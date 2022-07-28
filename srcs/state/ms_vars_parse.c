/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_vars_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 13:30:12 by nmathieu          #+#    #+#             */
/*   Updated: 2022/07/04 12:25:31 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms/state.h"
#include <stdlib.h>

static int	ms_var_parse(char **name, char **value, char *name_eq_value)
{
	size_t	i;

	i = 0;
	while (name_eq_value[i] && name_eq_value[i] != '=')
		i++;
	if (!name_eq_value[i])
		return (0);
	*name = ms_str_create(name_eq_value, i);
	if (!*name)
		return (-1);
	*value = ms_str_dup(name_eq_value + i + 1);
	if (!*value)
		return (free(*name), -1);
	return (1);
}

bool	ms_vars_parse(t_ms_vars *self, char **envp)
{
	char	*name;
	char	*value;
	int		ret;

	while (*envp)
	{
		ret = ms_var_parse(&name, &value, *envp);
		if (ret == -1)
			return (false);
		if (ret == 1 && !ms_var_set(self, name, value, true))
			return (false);
		envp++;
	}
	return (true);
}
