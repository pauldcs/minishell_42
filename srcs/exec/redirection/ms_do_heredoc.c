/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_do_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pducos <pducos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 18:52:46 by pducos            #+#    #+#             */
/*   Updated: 2022/06/26 21:52:42 by pducos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "ms/utils/str.h"

int	ms_do_heredoc(char *contents)
{
	int	fd;

	fd = open("tmp_here_doc", O_CREAT | O_TRUNC | O_WRONLY, 0666);
	if (fd == -1
		|| write(fd, contents, ms_str_len(contents) + 1) == -1
		|| close(fd) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
