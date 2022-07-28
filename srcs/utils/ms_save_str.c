/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_save_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pducos <pducos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 14:17:35 by pducos            #+#    #+#             */
/*   Updated: 2022/07/04 00:09:06 by pducos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include "ms/utils/mem.h"
#include "ms/utils/str.h"

char	*ms_save_str(const char *str)
{
	char	*save;
	size_t	size;

	if (str)
	{
		size = ms_str_len(str);
		save = malloc(++size);
		if (save)
			ms_mem_copy(save, str, size);
		return (save);
	}
	return (NULL);
}
