/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_putdstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 13:30:42 by nmathieu          #+#    #+#             */
/*   Updated: 2022/07/04 13:55:08 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stddef.h>
#include <stdbool.h>

static void	ms_putdchar(int fd, char c)
{
	if (c == '\n')
		write(fd, "\\n", 2);
	else if (c == '\t')
		write(fd, "\\t", 2);
	else if (c == '\\')
		write(fd, "\\\\", 2);
	else
		write(fd, &c, 1);
}

static void	ms_putdstr_fd(int fd, const char *str)
{
	const char	*t;

	while (*str)
	{
		if (' ' > *str || *str > '~')
		{
			ms_putdchar(fd, *str++);
			continue ;
		}
		t = str;
		while (' ' <= *str && *str <= '~')
			str++;
		if (str == t)
			str++;
		else
			write(fd, t, str - t);
	}
}

void	ms_putdstr(const char *str)
{
	ms_putdstr_fd(STDOUT_FILENO, str);
}

void	ms_putderr(const char *str)
{
	ms_putdstr_fd(STDERR_FILENO, str);
}
