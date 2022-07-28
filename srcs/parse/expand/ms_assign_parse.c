/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_assign_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 17:43:24 by nmathieu          #+#    #+#             */
/*   Updated: 2022/07/25 20:51:46 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms/parse/expand.h"
#include <stdbool.h>
#include <stdlib.h>

inline static bool	is_alpha(char c)
{
	return (false
		|| ('A' <= c && c <= 'Z')
		|| ('a' <= c && c <= 'z')
		|| c == '_');
}

inline static bool	is_digit(char c)
{
	return ('0' <= c && c <= '9');
}

static size_t	skip_identifier(const char *word)
{
	const char	*start;

	start = word;
	if (!is_alpha(*word))
		return (0);
	word++;
	while (is_alpha(*word) || is_digit(*word))
		word++;
	return (word - start);
}

static bool	make_assign(
				t_ms_assign *result,
				const char *name,
				size_t name_len,
				const char *value)
{
	result->name = ms_str_create(name, name_len);
	if (!result->name)
		return (false);
	result->value = ms_str_dup(value);
	if (!result->value)
		return (free(result->name), false);
	return (true);
}

int	ms_assign_parse(t_ms_assign *result, const char *word)
{
	const char	*name;
	size_t		name_len;

	name = word;
	name_len = skip_identifier(word);
	if (name_len == 0)
		return (0);
	word += name_len;
	if (*word == '=')
	{
		result->append = false;
		word += 1;
	}
	else if (*word == '+' && *(word + 1) == '=')
	{
		result->append = true;
		word += 2;
	}
	else
		return (0);
	if (!make_assign(result, name, name_len, word))
		return (-1);
	return (1);
}
