/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_vars_to_strs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 20:26:50 by nmathieu          #+#    #+#             */
/*   Updated: 2022/07/25 20:55:44 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms/state.h"
#include "ms/utils/alloc.h"
#include <stdlib.h>

static char	*var_to_str(t_ms_var *var)
{
	char	*ret;
	char	*cur;

	ret = ms_alloc(ms_str_len(var->name) + ms_str_len(var->value) + 2);
	if (!ret)
		return (NULL);
	cur = ret;
	cur = ms_str_copy(cur, var->name);
	*(cur++) = '=';
	cur = ms_str_copy(cur, var->value);
	return (ret);
}

static void	free_2d(char **p, size_t count)
{
	while (count)
		free(p[--count]);
	free(p);
}

char	**ms_vars_to_strs(t_ms_var *vars, size_t count)
{
	char		**ret;
	size_t		i;
	size_t		j;

	ret = ms_alloc_array(count + 1, sizeof(char *));
	if (!ret)
		return (NULL);
	i = 0;
	j = 0;
	while (i < count)
	{
		if (vars[i].exported && vars[i].value)
		{
			ret[j] = var_to_str(&vars[i]);
			if (!ret[j])
				return (free_2d(ret, j), NULL);
			j++;
		}
		i++;
	}
	ret[j] = NULL;
	return (ret);
}
