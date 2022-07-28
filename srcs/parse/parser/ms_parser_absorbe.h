/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser_absorbe.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 00:15:39 by nmathieu          #+#    #+#             */
/*   Updated: 2022/07/04 17:10:54 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_PARSER_ABSORBE_H
# define MS_PARSER_ABSORBE_H

# include "ms/parse/parser.h"
# include "ms/parse/token.h"
# include "ms/parse/ast.h"
# include <stdbool.h>
# include <stddef.h>

// Pushes a new scope onto the stack.
bool			ms_parser_push_scope(t_ms_parser *self, t_ms_ast **ast);

bool			ms_parser_push_paren(t_ms_parser *self, size_t index);

// Adds a command to the parser.
bool			ms_parser_add_cmd(t_ms_parser *self, t_ms_command *cmd);

// Adds a binary operation to the parser.
bool			ms_parser_add_binop(t_ms_parser *self, t_ms_ast_kind kind);

// Adds a closing parenthesis to the parser.
bool			ms_parser_add_cparen(
					t_ms_parser *self,
					struct s_ms_syn_cparen *cparen);

// Adds an open parenthesis to the parser.
bool			ms_parser_add_oparen(t_ms_parser *self);

t_ms_ast		**ms_parser_get_op_pos(t_ms_parser *self, t_ms_ast_kind kind);

#endif
