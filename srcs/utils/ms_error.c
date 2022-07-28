/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 13:08:23 by pducos            #+#    #+#             */
/*   Updated: 2022/07/25 20:24:05 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdbool.h>
#include <unistd.h>
#include <stddef.h>
#include "ms/utils/mem.h"

#define BUF_SIZE 4096

static void	write_to_buf(char *buf, size_t *cur, const void *data, size_t count)
{
	if (count >= BUF_SIZE - *cur)
		count = BUF_SIZE - *cur;
	ms_mem_copy(buf + *cur, data, count);
	*cur += count;
}

static void	put_int(char *buf, size_t *cur, int c)
{
	char	nbr[11];
	long	n;
	int		i;

	n = (long)c;
	if (!n)
	{
		write_to_buf(buf, cur, "0", 1);
		return ;
	}
	if (n < 0)
		n *= -1;
	i = 11;
	while (n)
	{
		nbr[--i] = (n % 10) | 0x30;
		n /= 10;
	}
	if (c < 0)
		nbr[--i] = '-';
	write_to_buf(buf, cur, nbr + i, 11 - i);
}

static void	put_str(char *buf, size_t *cur, const char *s)
{
	char	*tmp;

	if (!s)
	{
		write_to_buf(buf, cur, "(null)", 6);
		return ;
	}
	tmp = (char *)s;
	while (*s)
		s++;
	write_to_buf(buf, cur, tmp, s - tmp);
}

static void	write_all(const char *buf, size_t s)
{
	ssize_t	c;

	while (s != 0)
	{
		c = write(STDERR_FILENO, buf, s);
		if (c == -1)
			break ;
		s -= c;
	}
}

void	ms_error(const char *str, ...)
{
	va_list	ap;
	char	buf[BUF_SIZE];
	size_t	cur;

	cur = 0;
	va_start(ap, str);
	while (*str)
	{
		if (*str != '%')
			write_to_buf(buf, &cur, str, 1);
		else if (*++str)
		{
			if (*str == 's')
				put_str(buf, &cur, va_arg(ap, char *));
			else if (*str == 'd')
				put_int(buf, &cur, va_arg(ap, int));
		}
		str++;
	}
	write_all(buf, cur);
	va_end(ap);
}
