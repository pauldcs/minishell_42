/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_file_append.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pducos <pducos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 14:24:02 by pducos            #+#    #+#             */
/*   Updated: 2022/07/03 13:49:49 by pducos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "ms/exec/ms_general.h"
#include "ms/utils/io.h"
#include "ms/state.h"
#include <stdlib.h>

int	ms_file_append(const char *filename)
{
	int	fd;

	if (ms_file_exists(filename))
	{
		if (!ms_file_is_writable(filename))
			return (ms_error("%s: %s: Permission denied\n", g_ms.exec_name,
					filename), -1);
	}
	fd = open(filename, O_CREAT | O_APPEND | O_WRONLY, 0666);
	if (fd == -1)
		return (ms_error("%s: %s: No such file or directory\n", g_ms.exec_name,
				filename), -1);
	return (fd);
}
