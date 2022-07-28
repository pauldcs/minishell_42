/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_reader.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 17:52:49 by nmathieu          #+#    #+#             */
/*   Updated: 2022/06/10 21:43:39 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_READER_H
# define AST_READER_H

# include "ms/parse/ast.h"
# include "ms/parse/syn_reader.h"
# include "ms/parse/parser.h"
# include <stdbool.h>

// Stores the state required to parse tokens.
//
// Note that this parser is also responsible for printing error messages in
// case of errors.
typedef struct s_ms_ast_reader
{
	t_ms_syn_reader	syn_reader;
	t_ms_parser		parser;
	bool			exhausted;
}	t_ms_ast_reader;

// Initializes a `t_ms_ast_reader` instance.
bool	ms_ast_reader_init(t_ms_ast_reader *self, int fd);

// Frees the resources allocated for a `t_ms_ast_reader` instance.
void	ms_ast_reader_deinit(t_ms_ast_reader *self);

// Tries to parse an `t_ms_ast` instance from the inner file descriptor.
//
// Returns:
// -1  - An unexpected error occured.
//  0  - No more ASTs can be produced from the file. `result` is left undefined.
//  1  - `result` has been updated with a valid AST instance.
int		ms_ast_reader_next(t_ms_ast_reader *self, t_ms_ast **result);

#endif
