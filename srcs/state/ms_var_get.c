/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_var_get.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 18:07:22 by nmathieu          #+#    #+#             */
/*   Updated: 2022/06/30 13:14:13 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms/state.h"

static bool	eq(t_ms_str a, char *b)
{
	while (a.len && *b)
	{
		if (*a.s != *b)
			return (false);
		a.s++;
		a.len--;
		b++;
	}
	return (!a.len && !*b);
}

const char	*ms_var_get(t_ms_vars *self, t_ms_str name)
{
	size_t	i;

	i = 0;
	while (i < self->len)
	{
		if (eq(name, self->buf[i].name))
			return (self->buf[i].value);
		i++;
	}
	return (NULL);
}
