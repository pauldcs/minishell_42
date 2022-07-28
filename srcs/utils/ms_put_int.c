/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pducos <pducos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 01:47:53 by pducos            #+#    #+#             */
/*   Updated: 2022/06/11 09:28:19 by pducos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <unistd.h>

size_t	ms_put_int(int c, int fd)
{
	char	nbr[11];
	long	n;
	int		i;

	n = (long)c;
	if (n)
	{
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
		return (write(fd, &nbr[i], 11 - i));
	}
	return (write(fd, "0", 1));
}
