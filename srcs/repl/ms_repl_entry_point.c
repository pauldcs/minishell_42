/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_repl_entry_point.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 11:25:13 by nmathieu          #+#    #+#             */
/*   Updated: 2022/07/28 10:51:21 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include "ms/utils/str.h"
#include "ms/utils/alloc.h"
#include "ms/utils/mem.h"
#include "ms/exec.h"
#include "./ms_repl_engine.h"
#include <unistd.h>

bool	ms_repl_push_char(t_ms_repl_engine *engine, char c);
bool	ms_submit_history(t_ms_repl_engine *engine);

static char	*readline_with_prompt(t_ms_str varname)
{
	const char	*prompt;

	prompt = ms_var_get(&g_ms.vars, varname);
	if (!prompt)
		return (readline(""));
	return (readline(prompt));
}

static void	interrupted(t_ms_repl_engine *engine)
{
	g_ms.interrupted = false;
	ms_repl_engine_reset(engine);
	dup2(g_ms.stdin, STDIN_FILENO);
	engine->first_prompt = true;
	engine->cmd_buf.len = 0;
	engine->here_doc.len = 0;
}

static int	process_line(t_ms_repl_engine *self, char *line, t_ms_ast **ast)
{
	int	ret;

	ret = ms_repl_engine_absorbe(self, line, ast);
	if (ret == -2)
	{
		(free(line), ms_submit_history(self), ms_repl_engine_reset(self));
		g_ms.status = 2;
		return (0);
	}
	if (ret == -1)
		return (free(line), -1);
	if (ret == 0)
	{
		self->first_prompt = false;
		(ms_repl_push_char(self, '\n'), ms_sigset_prompt2());
		return (0);
	}
	if (ret == 1 && !line && !*ast)
		return (2);
	(ms_submit_history(self), ms_syner_send_here_docs(&self->syner));
	(free(line), ms_repl_engine_reset(self));
	return (1);
}

static int	next_ast(t_ms_repl_engine *self, t_ms_ast **ast)
{
	char	*line;
	int		ret;

	while (true)
	{
		if (self->first_prompt)
			line = readline_with_prompt((t_ms_str){"PS1", 3});
		else
			line = readline_with_prompt((t_ms_str){"PS2", 3});
		if (g_ms.interrupted)
		{
			(interrupted(self), free(line));
			continue ;
		}
		if (line && !ms_vec_append((t_ms_vec *)&self->cmd_buf, line,
				ms_str_len(line), sizeof(char)))
			return (free(line), -1);
		ret = process_line(self, line, ast);
		if (ret == 0)
			continue ;
		return (ret);
	}
}

bool	ms_repl_entry_point(void)
{
	t_ms_repl_engine	engine;
	int					ret;
	t_ms_ast			*ast;

	rl_outstream = stderr;
	ms_repl_engine_init(&engine);
	while (true)
	{
		ret = next_ast(&engine, &ast);
		if (ret == 2)
			break ;
		if (ret == -1)
			return (clear_history(), ms_repl_engine_deinit(&engine), false);
		ms_sigset_command();
		ms_execute_ast(ast);
		ms_sigset_prompt();
		ms_ast_free(ast);
		if (g_ms.exit_called)
			break ;
	}
	write(STDERR_FILENO, "exit\n", 5);
	return (clear_history(), ms_repl_engine_deinit(&engine), true);
}
