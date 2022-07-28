/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_syn_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 02:27:30 by nmathieu          #+#    #+#             */
/*   Updated: 2022/07/05 16:23:06 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms/parse/syn.h"
#include <stdlib.h>

void	ms_syn_free(t_ms_syn *self)
{
	size_t	i;

	if (self->kind == MS_SYN_CMD)
		ms_command_free(&self->cmd);
	else if (self->kind == MS_SYN_CPAREN)
	{
		i = 0;
		while (i < self->cparen.iord_count)
			ms_iord_free(&self->cparen.iords[i++]);
		if (self->cparen.iord_count)
			free(self->cparen.iords);
	}
}
