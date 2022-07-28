/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_push_expanded.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 12:57:10 by nmathieu          #+#    #+#             */
/*   Updated: 2022/07/25 20:51:17 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms/utils/str.h"
#include "ms/utils/alloc.h"
#include "ms/utils/mem.h"
#include "ms/parse/expand.h"
#include <stdlib.h>

inline static void	free_and_assign(char **s, char *to_assign)
{
	free(*s);
	*s = to_assign;
}

static void	free_vec(t_ms_vec *vec)
{
	if (!vec->cap)
		return ;
	while (vec->len)
		free(((char **)vec->buf)[--vec->len]);
	free(vec->buf);
}

bool	ms_push_expanded(char *word, t_ms_vec *vec)
{
	size_t		j;
	char		*expanded;
	bool		worked;
	t_ms_vec	fields;

	ms_mem_set(&fields, 0x00, sizeof(t_ms_vec));
	expanded = ms_expand_tild(word);
	free_and_assign(&expanded, ms_expand_vars(expanded));
	if (!expanded || !ms_split_fields(&fields, expanded))
		return (free_vec(&fields), false);
	free(expanded);
	j = 0;
	while (j < fields.len)
	{
		if (!ms_expand_pathname(vec, ((char **)fields.buf)[j], &worked))
			return (free_vec(&fields), false);
		if (!worked)
			ms_remove_quotes(((char **)vec->buf)[vec->len - 1]);
		j++;
	}
	free_vec(&fields);
	return (true);
}
