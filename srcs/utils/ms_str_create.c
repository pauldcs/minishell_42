/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_str_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 00:12:54 by nmathieu          #+#    #+#             */
/*   Updated: 2022/07/04 12:26:33 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms/utils/alloc.h"
#include "ms/utils/str.h"
#include "ms/utils/mem.h"

char	*ms_str_create(const char *s, size_t len)
{
	char	*ret;

	ret = ms_alloc(len + 1);
	if (!ret)
		return (NULL);
	ms_mem_copy(ret, s, len);
	ret[len] = '\0';
	return (ret);
}
