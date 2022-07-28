/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_put_sig.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 09:17:51 by pducos            #+#    #+#             */
/*   Updated: 2022/07/08 17:44:09 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms/exec/ms_signals.h"
#include "ms/utils/io.h"
#include <unistd.h>

void	ms_put_sig(int sig_code)
{
	static const char	*siglist[] = {\
		"",
		MS_SIGHUP, MS_SIGINT,
		MS_SIGQUIT, MS_SIGILL,
		MS_SIGTRAP, MS_SIGABRT,
		MS_SIGEMT, MS_SIGFPE,
		MS_SIGKILL, MS_SIGBUS,
		MS_SIGSEGV, MS_SIGSYS,
		MS_SIGPIPE, MS_SIGALRM,
		MS_SIGTERM, MS_SIGURG,
		MS_SIGSTOP, MS_SIGTSTP,
		MS_SIGCONT, MS_SIGCHLD,
		MS_SIGTTIN, MS_SIGTTOU,
		MS_SIGIO, MS_SIGXCPU,
		MS_SIGXFSZ, MS_SIGVTALRM,
		MS_SIGPROF, MS_SIGWINCH,
		MS_SIGINFO, MS_SIGUSR1,
		MS_SIGUSR2
	};

	if (sig_code != 13 && sig_code < 32)
		ms_error("%s: %d\n", siglist[sig_code], sig_code);
}
