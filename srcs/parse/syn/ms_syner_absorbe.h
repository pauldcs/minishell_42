/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_syner_absorbe.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 23:05:24 by nmathieu          #+#    #+#             */
/*   Updated: 2022/07/04 16:52:07 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_SYNER_ABSORBE_H
# define MS_SYNER_ABSORBE_H

# include "ms/parse/syner.h"

bool		ms_syner_parse_basic_iord(
				t_ms_syner *self,
				t_ms_iord_kind kind,
				char *word);
bool		ms_syner_parse_here_doc(t_ms_syner *self, char *raw_delim);

t_ms_syn_r	ms_syner_append_word(t_ms_syner *self, char *word);

typedef t_ms_syn_r	(*t_ms_syner_state_fn)(
						t_ms_syner *self,
						t_ms_tok *token,
						t_ms_syn *result);

t_ms_syn_r	ms_syner_state_init(
				t_ms_syner *self,
				t_ms_tok *token,
				t_ms_syn *result);
t_ms_syn_r	ms_syner_state_command(
				t_ms_syner *self,
				t_ms_tok *token,
				t_ms_syn *result);
t_ms_syn_r	ms_syner_state_command_end(
				t_ms_syner *self,
				t_ms_tok *token,
				t_ms_syn *result);
t_ms_syn_r	ms_syner_state_cmd_read(
				t_ms_syner *self,
				t_ms_tok *token,
				t_ms_syn *result);
t_ms_syn_r	ms_syner_state_cmd_write(
				t_ms_syner *self,
				t_ms_tok *token,
				t_ms_syn *result);
t_ms_syn_r	ms_syner_state_cmd_append(
				t_ms_syner *self,
				t_ms_tok *token,
				t_ms_syn *result);
t_ms_syn_r	ms_syner_state_cmd_here_doc(
				t_ms_syner *self,
				t_ms_tok *token,
				t_ms_syn *result);
t_ms_syn_r	ms_syner_state_oparen(
				t_ms_syner *self,
				t_ms_tok *token,
				t_ms_syn *result);
t_ms_syn_r	ms_syner_state_cparen(
				t_ms_syner *self,
				t_ms_tok *token,
				t_ms_syn *result);
t_ms_syn_r	ms_syner_state_cpar_read(
				t_ms_syner *self,
				t_ms_tok *token,
				t_ms_syn *result);
t_ms_syn_r	ms_syner_state_cpar_write(
				t_ms_syner *self,
				t_ms_tok *token,
				t_ms_syn *result);
t_ms_syn_r	ms_syner_state_cpar_append(
				t_ms_syner *self,
				t_ms_tok *token,
				t_ms_syn *result);
t_ms_syn_r	ms_syner_state_cpar_here_doc(
				t_ms_syner *self,
				t_ms_tok *token,
				t_ms_syn *result);
t_ms_syn_r	ms_syner_state_and_if(
				t_ms_syner *self,
				t_ms_tok *token,
				t_ms_syn *result);
t_ms_syn_r	ms_syner_state_or_if(
				t_ms_syner *self,
				t_ms_tok *token,
				t_ms_syn *result);
t_ms_syn_r	ms_syner_state_pipe(
				t_ms_syner *self,
				t_ms_tok *token,
				t_ms_syn *result);
t_ms_syn_r	ms_syner_state_seq(
				t_ms_syner *self,
				t_ms_tok *token,
				t_ms_syn *result);

#endif
