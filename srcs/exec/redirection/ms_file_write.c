/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_file_write.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pducos <pducos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 14:23:34 by pducos            #+#    #+#             */
/*   Updated: 2022/07/03 13:50:51 by pducos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "ms/utils/io.h"
#include "ms/exec/ms_general.h"
#include "ms/state.h"
#include <stdlib.h>

int	ms_file_write(const char *filename)
{
	int	fd;

	fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0666);
	if (fd == -1)
		return (ms_error("%s: %s: Permission denied\n", g_ms.exec_name,
				filename), -1);
	return (fd);
}
