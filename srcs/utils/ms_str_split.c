/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_str_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 01:50:07 by pducos            #+#    #+#             */
/*   Updated: 2022/07/04 12:26:43 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms/utils/str.h"
#include "ms/exec/ms_general.h"
#include <stdbool.h>
#include <stdlib.h>

static size_t	word_num(char const *s, char c)
{
	size_t	wrds;

	wrds = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
			wrds++;
		while (*s && *s != c)
			s++;
	}
	return (wrds);
}

char	**ms_str_split(char const *s, char c)
{
	char	**split;
	size_t	wrd;
	size_t	size;

	size = word_num(s, c);
	split = malloc (sizeof(char *) * (size + 1));
	if (split == NULL)
		return (NULL);
	while (*s && (*s == c))
		s++;
	while (*s)
	{
		wrd = 0;
		while (s[wrd] && (s[wrd] != c))
			wrd++;
		if (wrd)
		{
			*(split++) = ms_str_create(s, wrd);
			s += wrd;
		}
		else
			s++;
	}
	*split = NULL;
	return (split - size);
}
