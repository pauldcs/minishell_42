/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_str_append.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 18:37:40 by nmathieu          #+#    #+#             */
/*   Updated: 2022/07/12 18:48:26 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms/utils/alloc.h"
#include "ms/utils/str.h"
#include <stdlib.h>

bool	ms_str_append(char **self, const char *str)
{
	char			*tmp;

	tmp = ms_alloc(ms_str_len(*self) + ms_str_len(str) + 1);
	if (!tmp)
		return (false);
	ms_str_copy(ms_str_copy(tmp, *self), str);
	free(*self);
	*self = tmp;
	return (true);
}
