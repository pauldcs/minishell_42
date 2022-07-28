/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signals.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pducos <pducos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 22:15:40 by pducos            #+#    #+#             */
/*   Updated: 2022/06/11 09:25:43 by pducos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_SIGNALS_H
# define MS_SIGNALS_H

# define MS_SIGHUP 		"Hangup"
# define MS_SIGINT 		"Interrupt"
# define MS_SIGQUIT 	"Quit"
# define MS_SIGILL 		"Illegal instruction"
# define MS_SIGTRAP 	"BPT trace/trap"
# define MS_SIGABRT 	"ABORT instruction"
# define MS_SIGEMT 		"EMT instruction"
# define MS_SIGFPE 		"Floating point exception"
# define MS_SIGKILL		"Killed"
# define MS_SIGBUS 		"Bus error"
# define MS_SIGSEGV 	"Segmentation fault"
# define MS_SIGSYS 		"Bad system call"
# define MS_SIGPIPE 	"Broken pipe"
# define MS_SIGALRM 	"Alarm clock"
# define MS_SIGTERM 	"Terminated"
# define MS_SIGURG 		"Urgent IO condition"
# define MS_SIGSTOP 	"Stopped (signal)"
# define MS_SIGTSTP		"Stopped"
# define MS_SIGCONT 	"Continue"
# define MS_SIGCHLD 	"Child death or stop"
# define MS_SIGTTIN 	"Stopped (tty input)"
# define MS_SIGTTOU 	"Stopped (tty output)"
# define MS_SIGIO 		"I/O ready"
# define MS_SIGXCPU 	"CPU limit"
# define MS_SIGXFSZ 	"File limit"
# define MS_SIGVTALRM 	"Alarm (virtual)"
# define MS_SIGPROF 	"Alarm (profile)"
# define MS_SIGWINCH 	"Window changed"
# define MS_SIGINFO		"Information request"
# define MS_SIGUSR1 	"User signal 1"
# define MS_SIGUSR2 	"User signal 2"

#endif