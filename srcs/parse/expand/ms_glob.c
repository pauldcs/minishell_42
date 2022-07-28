/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_glob.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 10:51:50 by nmathieu          #+#    #+#             */
/*   Updated: 2022/07/26 10:55:40 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

bool	ms_contains_star(const char *word)
{
	bool	sq;
	bool	dq;

	sq = false;
	dq = false;
	while (*word)
	{
		if (*word == '\'' && !dq)
			sq = !sq;
		if (*word == '\"' && !sq)
			dq = !dq;
		if (*word == '*' && !sq && !dq)
			return (true);
		word++;
	}
	return (false);
}

static bool	__star(char *pattern, char *string);
bool		ms_glob(char *pattern, char *string);

static bool	__star(char *pattern, char *string)
{
	char	*tmp;

	tmp = pattern++;
	while (*(pattern - 1) == '*')
		tmp = pattern++;
	if (!*tmp)
		return (true);
	while (*string)
	{
		if (*string == *tmp)
		{
			if (ms_glob(--pattern, string))
				return (true);
		}
		string++;
	}
	return (false);
}

bool	ms_glob(char *pattern, char *string)
{
	if (*string == '.' && *pattern != '.')
		return (false);
	while (*pattern)
	{
		if (*pattern == '*')
		{
			pattern++;
			if (__star(pattern, string))
				return (true);
		}
		if (*pattern++ != *string)
			return (false);
		string++;
	}
	if (!*string)
		return (true);
	return (false);
}
