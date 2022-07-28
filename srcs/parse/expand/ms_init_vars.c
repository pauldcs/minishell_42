/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_init_vars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 20:36:04 by nmathieu          #+#    #+#             */
/*   Updated: 2022/07/25 20:57:12 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms/state.h"
#include <stdlib.h>
#include "ms/utils/alloc.h"
#include "ms/parse/expand.h"

static void	free_and_assign(char **old, char *new)
{
	free(*old);
	*old = new;
}

bool	ms_init_vars(t_ms_assign **ret, t_ms_assign *vars, size_t count)
{
	size_t		i;

	if (!count)
		return (true);
	*ret = ms_alloc_array(count, sizeof(t_ms_var));
	if (!*ret)
		return (false);
	i = (size_t)-1;
	while (++i < count)
	{
		(*ret)[i].name = ms_str_dup(vars[i].name);
		(*ret)[i].value = ms_expand_tild(vars[i].value);
		free_and_assign(&(*ret)[i].value, ms_expand_vars((*ret)[i].value));
		if (!(*ret)[i].name || !(*ret)[i].value)
		{
			free((*ret)[i].name);
			free((*ret)[i].value);
			while (i--)
				ms_assign_free(&(*ret)[i]);
			return (false);
		}
		(*ret)[i].append = vars[i].append;
		ms_remove_quotes((*ret)[i].value);
	}
	return (true);
}
