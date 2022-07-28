/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_submit_history.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 21:07:48 by nmathieu          #+#    #+#             */
/*   Updated: 2022/07/26 10:08:53 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_repl_engine.h"
#include <readline/history.h>

bool	ms_repl_push_char(t_ms_repl_engine *self, char c)
{
	if (!ms_vec_reserve((t_ms_vec *)&self->cmd_buf, 1, sizeof(char)))
		return (false);
	((char *)self->cmd_buf.buf)[self->cmd_buf.len++] = c;
	return (true);
}

bool	ms_submit_history(t_ms_repl_engine *self)
{
	if (!ms_repl_push_char(self, '\0'))
		return (false);
	add_history(self->cmd_buf.buf);
	self->cmd_buf.len = 0;
	return (true);
}
