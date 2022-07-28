/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pducos <pducos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 22:48:11 by pducos            #+#    #+#             */
/*   Updated: 2022/07/28 11:19:44 by pducos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms/state.h"
#include <stdbool.h>
#include "ms/utils/io.h"

static bool	exit_atoi(char *s, unsigned char *ret)
{
	bool			neg;

	neg = false;
	if (*s == '-' || *s == '+')
	{
		neg = *s == '-';
		s++;
	}
	if ('0' > *s || *s > '9')
		return (false);
	*ret = 0;
	while ('0' <= *s && *s <= '9')
	{
		*ret = 10 * *ret + (*s - '0');
		s++;
	}
	if (*s)
		return (false);
	if (neg)
		*ret = -*ret;
	return (true);
}

int	ms_exit(char **args, char **envp)
{
	unsigned char	ret;

	(void)envp;
	g_ms.exit_called = true;
	if (!args[0] || !args[1])
		return (g_ms.status);
	if (!exit_atoi(args[1], &ret))
		return (ms_error("%s: %s: %s: numeric argument required\n",
				g_ms.exec_name, args[0], args[1]), 2);
	if (args[2])
	{
		ms_error("%s: %s: too many arguments\n", g_ms.exec_name, args[0]);
		g_ms.exit_called = false;
		return (1);
	}
	return (ret);
}
