/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser_push_scope.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 00:19:15 by nmathieu          #+#    #+#             */
/*   Updated: 2022/06/30 11:23:53 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms/parse/parser.h"
#include "ms/parse/expand.h"
#include "ms/utils/io.h"
#include "ms/utils/alloc.h"
#include "ms/utils/mem.h"
#include "ms/utils/str.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

bool	ms_parser_push_scope(t_ms_parser *self, t_ms_ast **ast)
{
	if (!ms_vec_reserve((void *)&self->scopes, 1, sizeof(char **)))
		return (false);
	self->scopes.buf[self->scopes.len] = ast;
	self->scopes.len++;
	return (true);
}

bool	ms_parser_push_paren(t_ms_parser *self, size_t index)
{
	if (!ms_vec_reserve((void *)&self->parens, 1, sizeof(size_t)))
		return (false);
	self->parens.buf[self->parens.len] = index;
	self->parens.len++;
	return (true);
}
