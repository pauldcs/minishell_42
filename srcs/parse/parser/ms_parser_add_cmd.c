/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser_add_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 11:17:07 by nmathieu          #+#    #+#             */
/*   Updated: 2022/07/08 13:10:52 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms/parse/parser.h"
#include "ms/parse/ast.h"
#include "ms/parse/syn.h"
#include "ms/utils/alloc.h"
#include "./ms_parser_absorbe.h"
#include "ms/utils/debug.h"

bool	ms_parser_add_cmd(t_ms_parser *self, t_ms_command *cmd)
{
	ms_assert(!*self->scopes.buf[self->scopes.len - 1], "would override");
	*self->scopes.buf[self->scopes.len - 1] = ms_ast_create_cmd(cmd);
	return (*self->scopes.buf[self->scopes.len - 1] != NULL);
}
