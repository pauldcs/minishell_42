/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_vec_reserve.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:22:16 by nmathieu          #+#    #+#             */
/*   Updated: 2022/06/06 16:23:50 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms/utils/alloc.h"
#include <stdbool.h>
#include <stdint.h>

bool	ms_vec_reserve(t_ms_vec *self, size_t additional, size_t elem_size)
{
	size_t	amortizied;

	if (additional > SIZE_MAX - self->len)
		additional = SIZE_MAX;
	else
		additional += self->len;
	if (additional <= self->cap)
		return (true);
	if (self->cap > (SIZE_MAX - 4) / 2)
		amortizied = SIZE_MAX;
	else
		amortizied = self->cap * 2 + 4;
	if (amortizied > additional)
		return (ms_vec_realloc(self, amortizied, elem_size));
	else
		return (ms_vec_realloc(self, additional, elem_size));
}
