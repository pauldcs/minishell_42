/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_mem_copy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 03:11:01 by nmathieu          #+#    #+#             */
/*   Updated: 2022/05/31 11:33:56 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	ms_mem_copy(void *dst, const void *src, size_t len)
{
	while (len)
	{
		*(char *)dst = *(const char *)src;
		dst++;
		src++;
		len--;
	}
}
