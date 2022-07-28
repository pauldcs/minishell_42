/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 12:20:02 by nmathieu          #+#    #+#             */
/*   Updated: 2022/07/26 11:46:18 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms/state.h"

int	ms_unset(char **args, char **envp)
{
	(void)envp;
	if (!args[0])
		return (2);
	args++;
	while (*args)
	{
		ms_var_remove(&g_ms.vars, *args);
		args++;
	}
	return (0);
}
