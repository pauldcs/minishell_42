/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser_add_cparen.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 22:03:18 by nmathieu          #+#    #+#             */
/*   Updated: 2022/06/30 11:44:04 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms/parse/parser.h"
#include "ms/parse/syn.h"
#include "ms/utils/alloc.h"
#include "ms/utils/mem.h"
#include "ms/utils/debug.h"
#include "./ms_parser_absorbe.h"
#include <stdlib.h>
#include <stdbool.h>

bool	ms_parser_add_cparen(t_ms_parser *self, struct s_ms_syn_cparen *cparen)
{
	size_t	idx;

	ms_assert(self->parens.len, "no subshells :(");
	idx = self->parens.buf[--self->parens.len];
	if (cparen->iord_count)
	{
		(*self->scopes.buf[idx])->subsh.iord_count = cparen->iord_count;
		(*self->scopes.buf[idx])->subsh.iords = cparen->iords;
	}
	self->scopes.len = idx + 1;
	return (true);
}
