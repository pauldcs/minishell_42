/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_do_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 14:21:40 by pducos            #+#    #+#             */
/*   Updated: 2022/07/25 20:50:40 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms/parse/ast.h"
#include "ms/parse/expand.h"
#include "ms/exec/ms_redir.h"
#include "ms/utils/str.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int	__do_open(char *filename)
{
	int	fd;

	fd = ms_file_open(filename);
	if (fd == -1
		|| dup2(fd, STDIN_FILENO) == -1
		|| close (fd) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	__do_write(char *filename)
{
	int	fd;

	fd = ms_file_write(filename);
	if (fd == -1
		|| dup2(fd, STDOUT_FILENO) == -1
		|| close (fd) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	__do_append(char *filename)
{
	int	fd;

	fd = ms_file_append(filename);
	if (fd == -1
		|| dup2(fd, STDOUT_FILENO) == -1
		|| close (fd) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	__do_heredoc(char *contents)
{
	int	fds[2];

	if (pipe(fds) == -1
		|| write(fds[1], contents, ms_str_len(contents)) == -1
		|| close(fds[1]) == -1
		|| dup2(fds[0], STDIN_FILENO) == -1
		|| close(fds[0]) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ms_do_redirections(t_ms_expiord *iords, size_t n)
{
	while (n--)
	{
		if (iords->kind == MS_IORD_READ
			&& __do_open(iords->filename) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		else if (iords->kind == MS_IORD_WRITE
			&& __do_write(iords->filename) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		else if (iords->kind == MS_IORD_APPEND
			&& __do_append(iords->filename) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		else if (iords->kind == MS_IORD_HERE_DOC
			&& __do_heredoc(iords->here_doc) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		iords++;
	}
	return (EXIT_SUCCESS);
}
