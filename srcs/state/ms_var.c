/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_var.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 17:56:17 by nmathieu          #+#    #+#             */
/*   Updated: 2022/06/27 14:06:16 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms/state.h"
#include <stdlib.h>

void	ms_var_init(t_ms_var *self, char *name, char *value, bool exported)
{
	self->name = name;
	self->value = value;
	self->exported = exported;
}

void	ms_var_deinit(t_ms_var *self)
{
	free(self->name);
	if (self->value)
		free(self->value);
}
