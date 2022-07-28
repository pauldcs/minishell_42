/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_split_fields.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 14:52:59 by nmathieu          #+#    #+#             */
/*   Updated: 2022/07/07 15:43:07 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "ms/utils/alloc.h"
#include "ms/utils/str.h"

static bool	is_sep(char c, bool *in_dquote, bool *in_squote)
{
	if (!*in_dquote && c == '\'')
		*in_squote = !*in_squote;
	if (!*in_squote && c == '\"')
		*in_dquote = !*in_dquote;
	if (*in_squote || *in_dquote)
		return (false);
	return (c == ' ' || c == '\t' || c == '\n');
}

bool	ms_split_fields(t_ms_vec *vec, char *word)
{
	char	*start;
	bool	in_dquote;
	bool	in_squote;

	in_squote = false;
	in_dquote = false;
	while (true)
	{
		while (*word && is_sep(*word, &in_dquote, &in_squote))
			word++;
		if (!*word)
			break ;
		start = word;
		word++;
		while (*word && !is_sep(*word, &in_dquote, &in_squote))
			word++;
		if (!ms_vec_reserve(vec, 1, sizeof(char *)))
			return (false);
		((char **)vec->buf)[vec->len++] = ms_str_create(start, word - start);
		if (!*word)
			break ;
		word++;
	}
	return (true);
}
