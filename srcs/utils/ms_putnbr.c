/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 21:36:05 by nmathieu          #+#    #+#             */
/*   Updated: 2022/06/09 21:40:02 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <unistd.h>

static void	ms_putnbr_fd(int fd, size_t n)
{
	char	buf[64];
	char	*cur;

	if (n == 0)
	{
		write(fd, "0", n);
		return ;
	}
	cur = buf + 64;
	while (n)
	{
		*(--cur) = n % 10 + '0';
		n /= 10;
	}
	write(fd, cur, 64 - (cur - buf));
}

void	ms_putnbr_err(size_t n)
{
	ms_putnbr_fd(STDERR_FILENO, n);
}
