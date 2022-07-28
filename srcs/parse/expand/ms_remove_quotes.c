/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_remove_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 12:05:05 by nmathieu          #+#    #+#             */
/*   Updated: 2022/06/30 14:32:11 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms/utils/str.h"
#include "ms/utils/debug.h"
#include "ms/utils/mem.h"

#include <stdint.h>

static bool	ms_skip_until(size_t *i, char *word, char c)
{
	while (word[*i])
	{
		if (word[*i] == c)
			return (true);
		(*i)++;
	}
	return (false);
}

static void	remove_at(
				size_t at,
				size_t *prev,
				size_t *holes,
				char *word)
{
	if (*prev == SIZE_MAX)
	{
		(*holes)++;
		*prev = at;
		return ;
	}
	ms_mem_copy(
		word + *prev - *holes + 1,
		word + *prev + 1,
		at - *prev - 1);
	(*holes)++;
	*prev = at;
}

static void	ms_remove_matching(
				size_t *i,
				size_t *prev,
				size_t *holes,
				char *word)
{
	char	c;

	c = word[*i];
	remove_at(*i, prev, holes, word);
	(*i)++;
	ms_assert(ms_skip_until(i, word, c), "no matching quote found");
	remove_at(*i, prev, holes, word);
}

bool	ms_remove_quotes(char *word)
{
	size_t	holes;
	size_t	prev;
	size_t	i;

	holes = 0;
	i = 0;
	prev = SIZE_MAX;
	while (word[i])
	{
		if (word[i] == '\'' || word[i] == '\"')
			ms_remove_matching(&i, &prev, &holes, word);
		i++;
	}
	remove_at(i + 1, &prev, &holes, word);
	return (holes > 1);
}
