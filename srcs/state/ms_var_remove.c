/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_var_remove.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 12:23:04 by nmathieu          #+#    #+#             */
/*   Updated: 2022/07/09 12:49:49 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms/state.h"
#include <stdbool.h>
#include "ms/utils/str.h"
#include "ms/utils/mem.h"

bool	ms_var_remove(t_ms_vars *self, const char *name)
{
	size_t	i;

	i = 0;
	while (i < self->len)
	{
		if (ms_str_cmp(self->buf[i].name, name) == 0)
		{
			ms_var_deinit(&self->buf[i]);
			self->len--;
			ms_mem_copy(&self->buf[i], &self->buf[self->len], sizeof(t_ms_var));
			return (true);
		}
		i++;
	}
	return (false);
}
