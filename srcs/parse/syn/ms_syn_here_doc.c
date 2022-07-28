/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_syn_here_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 13:07:35 by nmathieu          #+#    #+#             */
/*   Updated: 2022/07/25 20:09:14 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms/parse/syner.h"
#include "ms/utils/debug.h"
#include "ms/utils/alloc.h"
#include "ms/utils/str.h"
#include <stddef.h>
#include <stdlib.h>

char	*ms_syner_here_doc(t_ms_syner *self)
{
	if (self->here_docs.complete == self->here_docs.len)
		return (NULL);
	return (self->here_docs.buf[self->here_docs.complete].delim);
}

bool	ms_syner_submit_here_doc(t_ms_syner *self, t_ms_str contents)
{
	ms_assert(
		self->here_docs.complete < self->here_docs.len,
		"unexpected here-doc submission");
	self->here_docs.buf[self->here_docs.complete].contents
		= ms_str_create(contents.s, contents.len);
	if (!self->here_docs.buf[self->here_docs.complete].contents)
		return (false);
	self->here_docs.complete++;
	return (true);
}

void	ms_syner_send_here_docs(t_ms_syner *self)
{
	size_t	i;

	ms_assert(
		self->here_docs.complete == self->here_docs.len,
		"tried to send here-docs but some are uninitialized");
	i = 0;
	while (i < self->here_docs.len)
	{
		*self->here_docs.buf[i].target = self->here_docs.buf[i].contents;
		free(self->here_docs.buf[i].delim);
		i++;
	}
	self->here_docs.len = 0;
	self->here_docs.complete = 0;
}
