/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 21:29:02 by nmathieu          #+#    #+#             */
/*   Updated: 2022/06/02 13:30:37 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

inline static void	ms_putstr_fd(int fd, const char *str)
{
	size_t	i;
	ssize_t	c;

	i = 0;
	while (str[i])
		i++;
	while (i)
	{
		c = write(fd, str, i);
		if (c <= 0)
			break ;
		i -= c;
		str += c;
	}
}

void	ms_putstr(const char *str)
{
	ms_putstr_fd(STDOUT_FILENO, str);
}

void	ms_puterr(const char *str)
{
	ms_putstr_fd(STDERR_FILENO, str);
}
