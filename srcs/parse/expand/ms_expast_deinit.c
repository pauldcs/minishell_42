/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expast_deinit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 18:17:28 by nmathieu          #+#    #+#             */
/*   Updated: 2022/07/25 20:36:35 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms/parse/expand.h"
#include <stdlib.h>

static void	ms_expast_cmd_deinit(struct s_ms_expast_cmd *self)
{
	size_t	i;

	i = 0;
	while (self->args[i])
		free(self->args[i++]);
	free(self->args);
	if (self->iord_count)
	{
		i = 0;
		while (i < self->iord_count)
			ms_expiord_deinit(&self->iords[i++]);
		free(self->iords);
	}
	if (self->override_count)
	{
		i = 0;
		while (i < self->override_count)
			ms_assign_free(&self->overrides[i++]);
		free(self->overrides);
	}
}

static void	ms_expast_subsh_deinit(struct s_ms_expast_subsh *self)
{
	size_t	i;

	if (self->iord_count)
	{
		i = 0;
		while (i < self->iord_count)
			ms_expiord_deinit(&self->iords[i++]);
		free(self->iords);
	}
}

void	ms_expast_deinit(t_ms_expast *self)
{
	if (self->kind == MS_AST_CMD)
		ms_expast_cmd_deinit(&self->cmd);
	else if (self->kind == MS_AST_SUBSH)
		ms_expast_subsh_deinit(&self->subsh);
}
