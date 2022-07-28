/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_file_is_execable copy.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pducos <pducos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 14:14:48 by pducos            #+#    #+#             */
/*   Updated: 2022/06/26 21:51:44 by pducos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ms/exec/ms_general.h"

int	ms_file_is_directory(const char *file)
{
	return (ms_file_status(file) & F_DIRECTORY);
}
