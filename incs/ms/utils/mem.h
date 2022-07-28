/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pducos <pducos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 20:18:10 by nmathieu          #+#    #+#             */
/*   Updated: 2022/07/28 11:16:49 by pducos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEM_H
# define MEM_H

# include <stddef.h>

// Copies `len` bytes from `src` to `dst`.
void	ms_mem_copy(void *dst, const void *src, size_t len);

// Sets the `n` first bytes pointed by `p` to the value `byte`.
void	ms_mem_set(void *p, char byte, size_t n);

// frees ressources pointed by `ptr` and sets it to NULL
void	ms_mem_free(void *ptr);

void	ms_free_array(char **arr);

void	f2d(char **p);

#endif
