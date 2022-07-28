/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_syner_absorbe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 23:04:14 by nmathieu          #+#    #+#             */
/*   Updated: 2022/07/04 16:02:18 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms/parse/syner.h"
#include "./ms_syner_absorbe.h"

static const t_ms_syner_state_fn	g_states[] = {
	ms_syner_state_init,
	ms_syner_state_command,
	ms_syner_state_command_end,
	ms_syner_state_cmd_read,
	ms_syner_state_cmd_write,
	ms_syner_state_cmd_append,
	ms_syner_state_cmd_here_doc,
	ms_syner_state_oparen,
	ms_syner_state_cparen,
	ms_syner_state_cpar_read,
	ms_syner_state_cpar_write,
	ms_syner_state_cpar_append,
	ms_syner_state_cpar_here_doc,
	ms_syner_state_and_if,
	ms_syner_state_or_if,
	ms_syner_state_pipe,
	ms_syner_state_seq,
};

t_ms_syn_r	ms_syner_absorbe(
				t_ms_syner *self,
				t_ms_tok *token,
				t_ms_syn *result)
{
	return ((*g_states[self->state])(self, token, result));
}
