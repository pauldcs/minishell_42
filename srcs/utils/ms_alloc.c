/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_alloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 16:13:57 by nmathieu          #+#    #+#             */
/*   Updated: 2022/07/09 00:44:08 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms/state.h"
#include "ms/utils/io.h"
#include "ms/utils/debug.h"

#include <stdlib.h>

void	*ms_alloc(size_t count)
{
	void	*ret;

	ms_assert(count, "tried to allocate a block of 0 bytes");
	ret = malloc(count);
	if (!ret)
		return (
			ms_puterr(g_ms.exec_name),
			ms_puterr(": out of memory\n"),
			NULL);
	return (ret);
}
