/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_syner.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 23:00:12 by nmathieu          #+#    #+#             */
/*   Updated: 2022/07/13 21:09:35 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms/parse/syner.h"
#include "ms/utils/mem.h"
#include <stdlib.h>
#include <stdbool.h>

void	ms_syner_init(t_ms_syner *self)
{
	ms_mem_set(self, 0x00, sizeof(t_ms_syner));
	self->state = MS_SYNER_INIT;
}

static void	free_here_docs(struct s_ms_syner_here_docs *here_docs)
{
	size_t	i;

	if (here_docs->cap)
	{
		i = 0;
		while (i < here_docs->len)
		{
			free(here_docs->buf[i].delim);
			free(here_docs->buf[i].contents);
			i++;
		}
		free(here_docs->buf);
	}
}

void	ms_syner_deinit(t_ms_syner *self)
{
	if (self->args.cap)
	{
		while (self->args.len)
			free(self->args.buf[--self->args.len]);
		free(self->args.buf);
	}
	if (self->iords.cap)
	{
		while (self->iords.len)
			ms_iord_free(&self->iords.buf[--self->iords.len]);
		free(self->iords.buf);
	}
	if (self->vars.cap)
	{
		while (self->vars.len)
			ms_assign_free(&self->vars.buf[--self->vars.len]);
		free(self->vars.buf);
	}
	free_here_docs(&self->here_docs);
}
