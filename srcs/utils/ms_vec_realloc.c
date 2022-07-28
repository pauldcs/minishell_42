/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_vec_realloc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:13:51 by nmathieu          #+#    #+#             */
/*   Updated: 2022/06/06 16:15:37 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include "ms/utils/debug.h"
#include "ms/utils/alloc.h"
#include "ms/utils/mem.h"

bool	ms_vec_realloc(t_ms_vec *self, size_t new_cap, size_t elem_size)
{
	void	*new_buf;

	ms_assert(new_cap > self->cap, "the new cap must be greater than the old");
	new_buf = ms_alloc_array(new_cap, elem_size);
	if (!new_buf)
		return (false);
	if (self->cap)
	{
		ms_mem_copy(new_buf, self->buf, self->len * elem_size);
		free(self->buf);
	}
	self->buf = new_buf;
	self->cap = new_cap;
	return (true);
}
