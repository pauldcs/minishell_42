/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_var_set.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 18:00:02 by nmathieu          #+#    #+#             */
/*   Updated: 2022/07/24 17:13:02 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms/state.h"
#include "ms/utils/str.h"
#include "ms/utils/alloc.h"
#include <stdlib.h>
#include <stdint.h>

bool	ms_var_set(t_ms_vars *self, char *name, char *value, bool export)
{
	size_t	i;

	i = 0;
	while (i < self->len)
	{
		if (ms_str_cmp(name, self->buf[i].name) == 0)
		{
			if (value && self->buf[i].value)
				free(self->buf[i].value);
			if (value)
				self->buf[i].value = value;
			free(name);
			self->buf[i].exported |= export;
			return (true);
		}
		i++;
	}
	if (!ms_vec_reserve((t_ms_vec *)self, 1, sizeof(t_ms_vec)))
		return (false);
	ms_var_init(&self->buf[self->len++], name, value, export);
	return (true);
}

bool	ms_var_append(t_ms_vars *self, char *name, char *value, bool export)
{
	size_t	i;

	i = 0;
	while (i < self->len)
	{
		if (ms_str_cmp(name, self->buf[i].name) == 0)
		{
			if (value && self->buf[i].value)
			{
				if (!ms_str_append(&self->buf[i].value, value))
					return (free(value), free(name), false);
				free(value);
			}
			if (value && !self->buf[i].value)
				self->buf[i].value = value;
			free(name);
			self->buf[i].exported |= export;
			return (true);
		}
		i++;
	}
	if (!ms_vec_reserve((t_ms_vec *)self, 1, sizeof(t_ms_vec)))
		return (free(name), free(value), false);
	ms_var_init(&self->buf[self->len++], name, value, export);
	return (true);
}

bool	ms_var_assign(t_ms_vars *self, t_ms_assign assign, bool export)
{
	if (assign.append)
		return (ms_var_append(self, assign.name, assign.value, export));
	else
		return (ms_var_set(self, assign.name, assign.value, export));
}

bool	ms_var_setup(
				t_ms_vars *self,
				const char *name,
				const char *value,
				bool export)
{
	char	*n;
	char	*v;

	n = ms_str_dup(name);
	if (!n)
		return (false);
	v = ms_save_str(value);
	if (value && !v)
		return (free(n), false);
	return (ms_var_set(self, n, v, export));
}
