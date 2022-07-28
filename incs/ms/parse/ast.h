/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 20:10:03 by nmathieu          #+#    #+#             */
/*   Updated: 2022/07/08 13:00:32 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "ms/state.h"
# include <stddef.h>
# include "ms/parse/command.h"

// The possible kind of an AST node.
typedef enum e_ms_ast_kind
{
	MS_AST_CMD,
	MS_AST_PIPE,
	MS_AST_AND_IF,
	MS_AST_OR_IF,
	MS_AST_SEQ,
	MS_AST_SUBSH,
}	t_ms_ast_kind;

// Returns the precedence of the provided AST node kind. Operations with higher
// precedence are higher in the final AST representation.
int			ms_ast_precedence(t_ms_ast_kind kind);

// A node of the Abstract Syntax Tree of a complex command.
typedef struct s_ms_ast	t_ms_ast;

// A node of the Abstract Syntax Tree of a command.
struct s_ms_ast
{
	t_ms_ast_kind	kind;

	union
	{
		t_ms_command	cmd;
		struct s_ms_ast_binop
		{
			t_ms_ast	*left;
			t_ms_ast	*right;
		}	binop;
		struct s_ms_ast_subsh
		{
			t_ms_ast		*root;

			t_ms_iord		*iords;
			size_t			iord_count;
		}	subsh;
	};
};

// Creates a new AST node representing a simple command.
t_ms_ast	*ms_ast_create_cmd(t_ms_command *command);

// Creates a new AST node representing a binary operator.
t_ms_ast	*ms_ast_create_binop(t_ms_ast_kind kind);

// Creates a new AST node representing a sub-shell.
t_ms_ast	*ms_ast_create_subsh(void);

// Frees the resources allocated for a `t_ms_ast` instance.
void		ms_ast_free(t_ms_ast *self);

// Displays the provided AST to the standard output.
void		ms_ast_show(t_ms_ast *self);

#endif
