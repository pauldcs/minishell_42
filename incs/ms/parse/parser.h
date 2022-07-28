/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 23:43:12 by nmathieu          #+#    #+#             */
/*   Updated: 2022/07/11 12:15:58 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "ms/parse/ast.h"
# include "ms/parse/syn.h"
# include <stdbool.h>
# include <stddef.h>

// Stores the state required to build an Abstract Syntax tree from a collection
// of tokens.
typedef struct s_ms_parser
{
	t_ms_ast		*result;

	struct s_ms_parser_scopes
	{
		t_ms_ast	***buf;
		size_t		cap;
		size_t		len;
	}	scopes;
	struct s_ms_parser_parens
	{
		size_t		*buf;
		size_t		cap;
		size_t		len;
	}	parens;
}	t_ms_parser;

// Initializes a new `t_ms_parser` instance.
bool			ms_parser_init(t_ms_parser *self);

// Frees the resources allocated for a `t_ms_parser` instance.
void			ms_parser_deinit(t_ms_parser *self);

// The result of the functions used to read from a parser.
typedef enum e_ms_parse_r
{
	MS_PARSE_R_FAILURE,
	MS_PARSE_R_SUCCESS,
	MS_PARSE_R_INCOMPLETE,
}	t_ms_parse_r;

// Absorbes a new token token.
t_ms_parse_r	ms_parser_absorbe(
					t_ms_parser *self,
					t_ms_syn *syn,
					t_ms_ast **result);

#endif
