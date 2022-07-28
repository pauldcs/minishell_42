/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser_add_oparen.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 10:00:29 by nmathieu          #+#    #+#             */
/*   Updated: 2022/06/30 14:24:33 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ms_parser_absorbe.h"
#include "ms/utils/debug.h"

bool	ms_parser_add_oparen(t_ms_parser *self)
{
	ms_assert(!*self->scopes.buf[self->scopes.len - 1], "would override!");
	*self->scopes.buf[self->scopes.len - 1]
		= ms_ast_create_subsh();
	if (!*self->scopes.buf[self->scopes.len - 1])
		return (false);
	if (!ms_parser_push_paren(self, self->scopes.len - 1)
		|| !ms_parser_push_scope(self,
			&(*self->scopes.buf[self->scopes.len - 1])->subsh.root))
		return (false);
	return (true);
}
