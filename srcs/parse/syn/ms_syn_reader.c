/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_syn_reader.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 01:50:33 by nmathieu          #+#    #+#             */
/*   Updated: 2022/06/11 14:45:16 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms/parse/syn_reader.h"
#include "ms/parse/tok_reader.h"
#include "ms/parse/syner.h"
#include <stdbool.h>

void	ms_syn_reader_init(t_ms_syn_reader *self, int fd)
{
	ms_tok_reader_init(&self->tokens, fd);
	ms_syner_init(&self->syner);
	self->reuse_token = false;
	self->exhausted = false;
}

void	ms_syn_reader_deinit(t_ms_syn_reader *self)
{
	ms_tok_reader_deinit(&self->tokens);
	ms_syner_deinit(&self->syner);
}
