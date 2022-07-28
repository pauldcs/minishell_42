/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 23:33:48 by nmathieu          #+#    #+#             */
/*   Updated: 2022/06/14 12:57:05 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALLOC_H
# define ALLOC_H

# include <stddef.h>
# include <stdbool.h>

// Allocates `count` bytes.
void	*ms_alloc(size_t count);

// Allocates `count * size` bytes.
void	*ms_alloc_array(size_t count, size_t size);

// A growable array.
typedef struct s_ms_vec
{
	void	*buf;
	size_t	cap;
	size_t	len;
}	t_ms_vec;

// Reallocates the provided block of memory.
bool	ms_vec_realloc(t_ms_vec *self, size_t new_cap, size_t elem_size);

// Reallocates the provided block of memory, making room for a least `add`
// bytes if required.
bool	ms_vec_reserve(t_ms_vec *self, size_t additional, size_t elem_size);

// Appends `n` elements from the `to_add` buffer at the end of the vector.
bool	ms_vec_append(t_ms_vec *self, const void *to_add, size_t n, size_t es);

#endif
