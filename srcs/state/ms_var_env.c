/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_var_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 18:15:10 by nmathieu          #+#    #+#             */
/*   Updated: 2022/07/25 20:31:14 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms/state.h"
#include "ms/utils/alloc.h"
#include "ms/parse/command.h"
#include "ms/utils/mem.h"
#include <stdlib.h>

char	**ms_vars_to_strs(t_ms_var *vars, size_t count);

static void	swap_and_free(t_ms_var *temp_buf, t_ms_vars *self, size_t count)
{
	size_t	i;

	i = 0;
	while (i < self->len)
	{
		free(self->buf[i].name);
		free(self->buf[i].value);
		i++;
	}
	if (self->cap)
		free(self->buf);
	self->buf = temp_buf;
	self->cap = count;
	self->len = count;
}

static bool	clone_vars(t_ms_var *dst, t_ms_var *src, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		dst[i].name = ms_str_dup(src[i].name);
		dst[i].value = ms_save_str(src[i].value);
		dst[i].exported = src[i].exported;
		i++;
		if (!dst[i - 1].name || (src[i - 1].value && !dst[i - 1].value))
		{
			while (i--)
			{
				free(dst[i].name);
				free(dst[i].value);
			}
			return (false);
		}
	}
	return (true);
}

static void	set_vars(t_ms_vars *self, t_ms_assign *vars, size_t *count)
{
	size_t	i;

	i = 0;
	while (i < *count)
	{
		if (!ms_var_assign(self, vars[i], true))
			break ;
		i++;
	}
	while (i < *count)
		ms_assign_free(&vars[i++]);
	if (*count)
		free(vars);
	*count = 0;
}

char	**ms_var_env(t_ms_vars *self, t_ms_assign *overrides, size_t *count)
{
	t_ms_var	*temp_buf;
	size_t		temp_len;
	char		**ret;

	temp_buf = ms_alloc_array(self->len, sizeof(t_ms_var));
	if (!temp_buf)
		return (NULL);
	temp_len = self->len;
	if (!clone_vars(temp_buf, self->buf, self->len))
		return (free(temp_buf), NULL);
	set_vars(self, overrides, count);
	ret = ms_vars_to_strs(self->buf, self->len);
	swap_and_free(temp_buf, self, temp_len);
	return (ret);
}
