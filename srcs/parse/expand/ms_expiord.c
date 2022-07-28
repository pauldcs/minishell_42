/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expiord.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 18:35:40 by nmathieu          #+#    #+#             */
/*   Updated: 2022/07/21 14:43:00 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms/parse/expand.h"
#include <stdlib.h>
#include "ms/utils/debug.h"

bool	ms_expiord_init(t_ms_expiord *self, const t_ms_iord *iord)
{
	self->kind = iord->kind;
	if (iord->kind == MS_IORD_HERE_DOC)
	{
		if (iord->here_doc.expand)
		{
			ms_assert(*iord->here_doc.contents, "uninit here-doc");
			self->here_doc = ms_expand_vars(*iord->here_doc.contents);
		}
		else
			self->here_doc = ms_str_dup(*iord->here_doc.contents);
		return (self->here_doc != NULL);
	}
	else
	{
		self->filename = ms_expand_filename(iord->filename);
		return (self->filename != NULL);
	}
}

void	ms_expiord_deinit(t_ms_expiord *self)
{
	if (self->kind == MS_IORD_HERE_DOC)
		free(self->here_doc);
	else
		free(self->filename);
}

bool	ms_expiord_array_init(t_ms_expiord **ret, t_ms_iord *iords, size_t c)
{
	size_t		i;

	if (!c)
		return (true);
	*ret = ms_alloc_array(c, sizeof(t_ms_expiord));
	if (!*ret)
		return (false);
	i = 0;
	while (i < c
		&& ms_expiord_init(&(*ret)[i], &iords[i]))
		i++;
	if (i != c)
	{
		while (i--)
			ms_expiord_deinit(&(*ret)[i]);
		return (free(*ret), false);
	}
	return (true);
}
