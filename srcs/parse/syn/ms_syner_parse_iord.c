/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_syner_parse_iord.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 23:51:57 by nmathieu          #+#    #+#             */
/*   Updated: 2022/07/05 17:07:42 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms/parse/ast.h"
#include "ms/parse/syner.h"
#include "ms/parse/expand.h"
#include "ms/utils/alloc.h"
#include <stdbool.h>
#include <stdlib.h>

bool	ms_syner_parse_basic_iord(
			t_ms_syner *self,
			t_ms_iord_kind kind,
			char *filename)
{
	if (!ms_vec_reserve((t_ms_vec *)&self->iords, 1, sizeof(t_ms_iord)))
		return (false);
	self->iords.buf[self->iords.len].kind = kind;
	self->iords.buf[self->iords.len].filename = ms_str_dup(filename);
	if (!self->iords.buf[self->iords.len].filename)
		return (false);
	self->iords.len++;
	return (true);
}

bool	ms_syner_parse_here_doc(
	t_ms_syner *self,
	char *raw_delim)
{
	char	*delim;

	delim = ms_str_dup(raw_delim);
	if (!delim)
		return (false);
	if (!ms_vec_reserve((t_ms_vec *)&self->iords, 1, sizeof(t_ms_iord)))
		return (free(delim), false);
	self->iords.buf[self->iords.len].here_doc.contents
		= ms_alloc(sizeof(char *));
	if (!self->iords.buf[self->iords.len].here_doc.contents)
		return (free(delim), false);
	*self->iords.buf[self->iords.len].here_doc.contents = NULL;
	self->iords.buf[self->iords.len].kind = MS_IORD_HERE_DOC;
	self->iords.buf[self->iords.len].here_doc.expand
		= !ms_remove_quotes(delim);
	self->iords.len++;
	if (!ms_vec_reserve((t_ms_vec *)&self->here_docs, 1, sizeof(t_ms_here_doc)))
		return (free(delim), false);
	self->here_docs.buf[self->here_docs.len].delim = delim;
	self->here_docs.buf[self->here_docs.len].contents = NULL;
	self->here_docs.buf[self->here_docs.len].target
		= self->iords.buf[self->iords.len - 1].here_doc.contents;
	self->here_docs.len++;
	return (true);
}
