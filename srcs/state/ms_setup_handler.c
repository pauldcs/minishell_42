/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_setup_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 14:05:12 by nmathieu          #+#    #+#             */
/*   Updated: 2022/07/25 20:52:48 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms/utils/io.h"
#include "ms/utils/mem.h"
#include "ms/state.h"

#include <readline/readline.h>
#include <stdbool.h>
#include <signal.h>
#include <unistd.h>

bool	ms_setup_handler(int signal, void (*handler)(int))
{
	struct sigaction	handler_info;

	ms_mem_set(&handler_info, 0x00, sizeof(struct sigaction));
	handler_info.sa_handler = handler;
	sigemptyset(&handler_info.sa_mask);
	if (sigaction(signal, &handler_info, NULL) != 0)
		(ms_error("%s: can't setup signal %d\n", g_ms.exec_name, signal), 0);
	return (true);
}

bool	ms_sigset_default(void)
{
	return (
		ms_setup_handler(SIGINT, SIG_DFL)
		&& ms_setup_handler(SIGQUIT, SIG_DFL));
}

bool	ms_sigset_command(void)
{
	return (
		ms_setup_handler(SIGINT, SIG_IGN)
		&& ms_setup_handler(SIGQUIT, SIG_IGN));
}
