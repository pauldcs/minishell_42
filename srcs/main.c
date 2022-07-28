/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 21:50:33 by nmathieu          #+#    #+#             */
/*   Updated: 2022/07/28 11:30:42 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms/fun.h"
#include "ms/state.h"
#include "ms/utils/io.h"

#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int	main(int ac, const char *const *av, char **envp)
{
	if (!isatty(STDIN_FILENO))
		return (ms_error("%s: ah ah, I see what you did there :)\n", av[0]), 1);
	if (ac != 1 || !ms_init_state(av[0], envp))
		return (1);
	ms_repl_entry_point();
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	return (ms_deinit_state(), g_ms.status);
}
