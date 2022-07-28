/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 12:35:56 by pducos            #+#    #+#             */
/*   Updated: 2022/07/26 11:45:22 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms/exec/ms_general.h"
#include "ms/parse/ast.h"
#include "ms/utils/io.h"
#include "ms/utils/str.h"
#include <unistd.h>
#include <stdlib.h>

static bool	put_str(const char *s)
{
	size_t	i;
	ssize_t	c;

	i = ms_str_len(s);
	while (i)
	{
		c = write(STDOUT_FILENO, s, i);
		if (c <= 0)
			return (false);
		i -= c;
		s += c;
	}
	return (true);
}

static bool	do_echoing(char **args)
{
	while (*args)
	{
		if (!put_str(*(args++)))
			return (false);
		if (*args && !put_str(" "))
			return (false);
	}
	return (true);
}

static bool	is_n_arg(char *arg)
{
	if (*(arg++) != '-')
		return (false);
	while (*arg == 'n')
		arg++;
	return (*arg == '\0');
}

int	ms_echo(char **args, char **envp)
{
	size_t	i;

	(void)envp;
	i = 1;
	while (args[i] && is_n_arg(args[i]))
		i++;
	if (i != 1)
	{
		if (!do_echoing(args + i))
			return (EXIT_FAILURE);
	}
	else
	{
		if (!do_echoing(args + 1))
			return (EXIT_FAILURE);
		if (!put_str("\n"))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
