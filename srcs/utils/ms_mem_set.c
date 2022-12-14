/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_mem_set.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 13:56:49 by nmathieu          #+#    #+#             */
/*   Updated: 2022/06/01 14:44:45 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	ms_mem_set(void *p, char byte, size_t n)
{
	while (n)
	{
		*(char *)p = byte;
		n--;
		p++;
	}
}
