/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 11:58:26 by nmathieu          #+#    #+#             */
/*   Updated: 2022/07/25 20:44:00 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms/parse/expand.h"
#include "ms/utils/alloc.h"
#include "ms/utils/mem.h"
#include <stdlib.h>

static void	free_output(t_ms_vec *output)
{
	while (output->len)
		free(((char **)output->buf)[--output->len]);
	free(output->buf);
}

char	**ms_expand_args(char **args, size_t count)
{
	t_ms_vec	output;

	ms_mem_set(&output, 0x00, sizeof(t_ms_vec));
	while (count)
	{
		if (!ms_push_expanded(*args, &output))
			return (free_output(&output), NULL);
		count--;
		args++;
	}
	if (!ms_vec_reserve(&output, 1, sizeof(char *)))
		return (free_output(&output), NULL);
	((char **)output.buf)[output.len++] = NULL;
	return (output.buf);
}
