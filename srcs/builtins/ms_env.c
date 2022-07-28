/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 23:35:41 by nmathieu          #+#    #+#             */
/*   Updated: 2022/07/08 23:44:41 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms/state.h"
#include "ms/utils/io.h"
#include <stdlib.h>
#include <unistd.h>

int	ms_env(char **args, char **envp)
{
	(void)args;
	while (*envp)
	{
		ms_putstr(*envp);
		write(STDOUT_FILENO, "\n", 1);
		envp++;
	}
	return (EXIT_SUCCESS);
}
