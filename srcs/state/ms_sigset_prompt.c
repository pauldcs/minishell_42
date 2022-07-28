/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_sigset_prompt.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 20:32:11 by nmathieu          #+#    #+#             */
/*   Updated: 2022/07/25 20:54:14 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <signal.h>
#include <unistd.h>
#include <readline/readline.h>
#include "ms/state.h"

bool	ms_setup_handler(int signal, void (*handler)(int _param));

static void	handle_prompt2_sigint(int _param)
{
	(void)_param;
	write(STDERR_FILENO, "\n", 1);
	close(STDIN_FILENO);
	rl_replace_line("", 1);
	g_ms.status = 130;
	g_ms.interrupted = true;
}

bool	ms_sigset_prompt2(void)
{
	return (
		ms_setup_handler(SIGINT, handle_prompt2_sigint)
		&& ms_setup_handler(SIGQUIT, SIG_IGN));
}

static void	handle_prompt_sigint(int _param)
{
	(void)_param;
	write(STDERR_FILENO, "\n", 1);
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
	g_ms.status = 130;
}

bool	ms_sigset_prompt(void)
{
	return (
		ms_setup_handler(SIGINT, handle_prompt_sigint)
		&& ms_setup_handler(SIGQUIT, SIG_IGN));
}
