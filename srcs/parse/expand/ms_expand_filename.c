/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_filename.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 13:38:42 by nmathieu          #+#    #+#             */
/*   Updated: 2022/07/25 20:43:56 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include "ms/parse/expand.h"

void	ms_parse_err_ambiguous_redirect(char *name);

static void	free_array_2d(char **args)
{
	size_t	i;

	i = 0;
	while (args[i])
		free(args[i++]);
	free(args);
}

char	*ms_expand_filename(char *word)
{
	char	**e;
	char	*ret;

	e = ms_expand_args(&word, 1);
	if (!e)
		return (NULL);
	if (!*e || e[1])
		return (ms_parse_err_ambiguous_redirect(word), free_array_2d(e), NULL);
	ret = *e;
	free(e);
	return (ret);
}
