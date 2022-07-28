/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_vec_append.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 12:48:33 by nmathieu          #+#    #+#             */
/*   Updated: 2022/06/20 15:38:04 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms/utils/alloc.h"
#include "ms/utils/mem.h"

bool	ms_vec_append(
			t_ms_vec *self,
			const void *to_add,
			size_t n,
			size_t elem_size)
{
	if (!ms_vec_reserve(self, n, elem_size))
		return (false);
	ms_mem_copy(self->buf + self->len * elem_size, to_add, n * elem_size);
	self->len += n;
	return (true);
}
