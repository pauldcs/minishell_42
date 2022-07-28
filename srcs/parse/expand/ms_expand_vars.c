/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_vars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 12:11:50 by nmathieu          #+#    #+#             */
/*   Updated: 2022/07/25 20:41:44 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms/utils/str.h"
#include "ms/utils/mem.h"
#include "ms/state.h"
#include <stddef.h>
#include "ms/utils/alloc.h"
#include "./ms_expand_vars.h"

static size_t	skip_until_dollar(const char *word, size_t *count, char *buf)
{
	size_t	i;
	bool	squote;
	bool	dquote;

	i = 0;
	squote = false;
	dquote = false;
	while (word[i] && (squote || word[i] != '$'))
	{
		if (word[i] == '\'' && !dquote)
			squote = !squote;
		if (word[i++] == '\"' && !squote)
			dquote = !dquote;
	}
	if (buf)
		ms_mem_copy(buf + *count, word, i);
	*count += i;
	if (word[i] && !word[i + 1])
	{
		if (buf)
			buf[*count] = '$';
		(*count)++;
	}
	i += word[i] != 0;
	return (i);
}

static size_t	skip_ident(const char *word)
{
	size_t	i;

	if (!*word)
		return (0);
	if (true
		&& (*word < 'a' || 'z' < *word)
		&& (*word < 'A' || 'Z' < *word)
		&& *word != '_')
		return (0);
	i = 1;
	while (word[i] && (false
			|| ('a' <= word[i] && word[i] <= 'z')
			|| ('A' <= word[i] && word[i] <= 'Z')
			|| ('0' <= word[i] && word[i] <= '9')
			|| word[i] == '_'))
		i++;
	return (i);
}

static void	variable(const char **word, size_t *count, char *buf)
{
	const size_t	i = skip_ident(*word);
	const char		*value;

	if (i != 0)
	{
		value = ms_var_get(&g_ms.vars, (t_ms_str){
				*word, i});
		if (value)
		{
			if (buf)
				ms_str_copy(buf + *count, value);
			*count += ms_str_len(value);
		}
		*word += i;
	}
	else
	{
		if (buf)
			buf[*count] = '$';
		(*count)++;
	}
}

static size_t	try_expand(const char *word, char *buf)
{
	size_t	count;

	count = 0;
	while (true)
	{
		word += skip_until_dollar(word, &count, buf);
		if (!*word)
			break ;
		else if (*word == '?')
		{
			if (buf)
				count += ms_expand_status(buf + count);
			else
				count += ms_expand_status(NULL);
			word++;
		}
		else if (*word != '\"' && *word != '\'')
			variable(&word, &count, buf);
	}
	return (count);
}

char	*ms_expand_vars(const char *arg)
{
	size_t	len;
	char	*ret;

	len = try_expand(arg, NULL);
	ret = ms_alloc(len + 1);
	if (!ret)
		return (NULL);
	try_expand(arg, ret);
	ret[len] = '\0';
	return (ret);
}
