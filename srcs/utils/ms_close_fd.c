/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_close_fd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 20:17:02 by pducos            #+#    #+#             */
/*   Updated: 2022/07/25 20:24:15 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ms_close_fd(int	*fd)
{
	if (*fd < 0)
		return (0);
	else if (close(*fd) == -1)
		return (-1);
	*fd = -1;
	return (0);
}
