/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_pathname.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 13:06:42 by nmathieu          #+#    #+#             */
/*   Updated: 2022/07/26 10:55:18 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms/parse/expand.h"
#include <dirent.h>
#include "ms/utils/mem.h"
#include "ms/utils/alloc.h"
#include "ms/utils/str.h"
#include <limits.h>
#include <stdlib.h>

bool		ms_contains_star(const char *word);
bool		ms_glob(char *pattern, char *string);

static bool	next_segment(char **pathname, char **segment, bool *is_dir)
{
	if (!**pathname)
		return (false);
	*segment = *pathname;
	while (**pathname && **pathname != '/')
		(*pathname)++;
	*is_dir = **pathname == '/';
	*segment = ms_str_create(*segment, *pathname - *segment);
	while (**pathname == '/')
		(*pathname)++;
	return (true);
}

static bool	expand_from(t_star_exp s);

static bool	do_expansion(t_star_exp s, char *seg, bool od)
{
	DIR				*dir;
	struct dirent	*e;
	size_t			t;
	char			*cur;

	if (!*s.path)
		dir = opendir(".");
	else
		dir = opendir(s.path);
	if (!dir)
		return (false);
	t = ms_str_len(s.path);
	while (true)
	{
		e = readdir(dir);
		if (!e)
			break ;
		if ((od && e->d_type != DT_DIR) || !ms_glob(seg, e->d_name))
			continue ;
		cur = ms_str_copy(s.path + t, e->d_name);
		if ((od && ms_str_copy(cur, "/"), true) && !expand_from(s))
			return (closedir(dir), false);
		s.path[t] = '\0';
	}
	return (closedir(dir), true);
}

// Recursively calls itself for every possible matching path.
static bool	expand_from(t_star_exp s)
{
	bool			only_dirs;
	char			*segment;

	if (!next_segment(&s.pathname, &segment, &only_dirs))
	{
		if (!ms_vec_reserve(s.vec, 1, sizeof(char *)))
			return (false);
		((char **)s.vec->buf)[s.vec->len] = ms_str_dup(s.path);
		if (!((char **)s.vec->buf)[s.vec->len])
			return (false);
		s.vec->len++;
		return (true);
	}
	if (!segment)
		return (false);
	if (!do_expansion(s, segment, only_dirs))
		return (free(segment), false);
	return (free(segment), true);
}

// Expand the provided generic pathname and prints the results to the standard
// output.
static bool	pathname_expand(t_ms_vec *vec, char *pathname)
{
	char		path[PATH_MAX];
	t_star_exp	s;

	s.vec = vec;
	s.path = path;
	s.pathname = pathname;
	if (*pathname == '/')
	{
		path[0] = '/';
		path[1] = '\0';
		s.pathname++;
		return (expand_from(s));
	}
	else
	{
		path[0] = '\0';
		return (expand_from(s));
	}
}

bool	ms_expand_pathname(t_ms_vec *vec, char *word, bool *worked)
{
	size_t		i;

	i = vec->len;
	*worked = true;
	if (ms_contains_star(word) && pathname_expand(vec, word) && vec->len > i)
		return (true);
	while (vec->len > i)
		free(((char **)vec->buf)[--vec->len]);
	if (!ms_vec_reserve(vec, 1, sizeof(char *)))
		return (false);
	((char **)vec->buf)[vec->len] = ms_str_dup(word);
	if (!((char **)vec->buf)[vec->len])
		return (false);
	vec->len++;
	*worked = false;
	return (true);
}
