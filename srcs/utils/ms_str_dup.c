/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_str_dup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 11:53:53 by pducos            #+#    #+#             */
/*   Updated: 2022/07/18 15:17:29 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include "ms/utils/str.h"
#include "ms/utils/mem.h"
#include "ms/utils/alloc.h"

char	*ms_str_dup(const char *str)
{
	const size_t	len = ms_str_len(str);
	char			*new;

	new = ms_alloc(len + 1);
	if (new == NULL)
		return (NULL);
	ms_mem_copy(new, str, len);
	new[len] = '\0';
	return (new);
}
