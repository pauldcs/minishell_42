/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_special_vars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 16:03:03 by nmathieu          #+#    #+#             */
/*   Updated: 2022/07/11 12:20:07 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms/state.h"
#include <stddef.h>
#include <limits.h>

static size_t	num_len(int n)
{
	size_t	result;

	if (n == INT_MIN)
		return (11);
	if (n == 0)
		return (1);
	result = 0;
	if (n < 0)
	{
		result++;
		n = -n;
	}
	while (n)
	{
		result++;
		n /= 10;
	}
	return (result);
}

size_t	ms_expand_status(char *buf)
{
	const size_t	len = num_len(g_ms.status);
	int				n;
	size_t			i;

	if (!buf)
		return (len);
	if (g_ms.status == INT_MIN)
		return (ms_str_copy(buf, "-2147483648"), len);
	n = g_ms.status;
	if (n < 0)
	{
		buf[0] = '-';
		n = -n;
	}
	i = len;
	while (i)
	{
		buf[--i] = n % 10 + '0';
		n /= 10;
	}
	return (len);
}
