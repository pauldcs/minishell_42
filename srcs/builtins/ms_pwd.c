/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 12:26:07 by pducos            #+#    #+#             */
/*   Updated: 2022/07/26 11:46:09 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms/exec/ms_general.h"
#include "ms/utils/io.h"
#include "ms/utils/str.h"
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>

int	ms_pwd(char **argv, char **envp)
{
	char	buf[PATH_MAX];

	(void)argv;
	(void)envp;
	if (!getcwd(buf, PATH_MAX))
	{
		ms_putstr("<unknown>\n");
		return (EXIT_FAILURE);
	}
	else
	{
		ms_putstr(buf);
		ms_putstr("\n");
		return (EXIT_SUCCESS);
	}
}
