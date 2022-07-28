/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_file_status.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pducos <pducos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 14:13:16 by pducos            #+#    #+#             */
/*   Updated: 2022/06/26 21:50:00 by pducos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include "ms/exec/ms_general.h"

int	ms_file_status(const char *name)
{
	struct stat	info;
	int			status;

	if (stat(name, &info) < 0)
		return (0);
	if (S_ISDIR (info.st_mode))
		return (F_EXISTS | F_DIRECTORY);
	status = F_EXISTS;
	if (info.st_mode & S_IXUSR)
		status |= F_EXECABLE;
	if (info.st_mode & S_IRUSR)
		status |= F_READABLE;
	return (status);
}
