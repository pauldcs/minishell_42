/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_alloc_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 11:52:36 by nmathieu          #+#    #+#             */
/*   Updated: 2022/06/06 16:16:57 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms/utils/alloc.h"

#include <stdint.h>

void	*ms_alloc_array(size_t count, size_t size)
{
	if (size != 0 && count > SIZE_MAX / size)
		return (ms_alloc(SIZE_MAX));
	else
		return (ms_alloc(size * count));
}
