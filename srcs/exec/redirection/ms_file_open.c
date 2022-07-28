/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_file_open.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pducos <pducos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 14:22:33 by pducos            #+#    #+#             */
/*   Updated: 2022/07/03 13:50:05 by pducos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "ms/exec/ms_general.h"
#include "ms/state.h"
#include "ms/utils/io.h"
#include <stdlib.h>

int	ms_file_open(const char *filename)
{
	int	fd;

	if (!ms_file_exists(filename))
		return (ms_error("%s: %s: No such file or directory\n", g_ms.exec_name,
				filename), -1);
	else if (!ms_file_is_readable(filename))
		return (ms_error("%s: %s: Permission denied\n", g_ms.exec_name,
				filename), -1);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (ms_error("%s: %s: Permission denied\n", g_ms.exec_name,
				filename), -1);
	return (fd);
}
