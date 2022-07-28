/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_fri_and_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 20:57:51 by nmathieu          #+#    #+#             */
/*   Updated: 2022/07/25 20:57:55 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

static size_t	__nbr_len(int nbr)
{
	int					size;
	int					sign;
	long				n;
	static const long	size_tab[] = {
		10, 100, 1000, 10000, 100000,
		1000000, 10000000,
		100000000, 1000000000,
		10000000000};

	n = (long)nbr;
	sign = 0;
	if (nbr < 0)
	{
		n *= -1;
		sign++;
	}
	size = 1;
	while (n >= size_tab[size - 1])
		size++;
	return (size + sign);
}

static char	*ms_generate_exit(int n)
{
	size_t	size;
	long	nbr;
	char	*new;

	size = __nbr_len(n);
	nbr = (long)n;
	new = malloc (size + 1 + 5);
	if (new == NULL)
		return (NULL);
	if (n < 0)
		nbr *= -1;
	new[size + 5] = 0x00;
	while (size--)
	{
		new[size + 5] = (nbr % 10) | 0x30;
		nbr /= 10;
	}
	new[0] = 'e';
	new[1] = 'x';
	new[2] = 'i';
	new[3] = 't';
	new[4] = ' ';
	if (n < 0)
		*new = '-';
	return (new);
}

void	ms_fri_and_exit(int status)
{
	char	*args[4];

	args[0] = "sh";
	args[1] = "-c";
	args[2] = ms_generate_exit(status);
	args[3] = NULL;
	execve("/usr/bin/sh", args, NULL);
}
