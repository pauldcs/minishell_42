/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 20:05:53 by nmathieu          #+#    #+#             */
/*   Updated: 2022/06/20 15:31:12 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "ms/parse/token.h"

# include <stddef.h>

# define MS_LEX_TOK_MASK 0x80000000

typedef enum e_ms_lex_state
{
	MS_LEX_INIT,
	MS_LEX_WORD,
	MS_LEX_SQUOTE,
	MS_LEX_DQUOTE,
	MS_LEX_AND,
	MS_LEX_OR,
	MS_LEX_GREAT,
	MS_LEX_LESS,
	MS_LEX_DONE,
	MS_LEX_EOF_F = MS_LEX_TOK_MASK,
	MS_LEX_NEWLINE_F,
	MS_LEX_WORD_F,
	MS_LEX_DAND_F,
	MS_LEX_OR_F,
	MS_LEX_DOR_F,
	MS_LEX_LESS_F,
	MS_LEX_DLESS_F,
	MS_LEX_GREAT_F,
	MS_LEX_DGREAT_F,
	MS_LEX_OPAREN_F,
	MS_LEX_CPAREN_F,
	MS_LEX_ERR_NOSQUOTE,
	MS_LEX_ERR_NODQUOTE,
}	t_ms_lex_state;

// The state of the lexical analyzer.
typedef struct s_ms_lexer
{
	t_ms_lex_state	state;
	struct s_ms_lexer_chars
	{
		char		*buf;
		size_t		cap;
		size_t		len;
	}	chars;
}	t_ms_lexer;

// Initializes a `t_ms_lex_state` instance.
void		ms_lexer_init(t_ms_lexer *self);

// Frees the resources allocated for a `t_ms_lex_state` instance.
void		ms_lexer_deinit(t_ms_lexer *self);

// The return-type of the `ms_lexer_absorbe` function.
//
// `FAILURE` indicates that that an unexpected error occured. A proper error
// message should already be displayed.
//
// `INCOMPLETE` indicates that another character should be passed to the lexer.
//
// `SUCCESS_SAME` indicates that the same character should be passed to the
// lexer. The result has been properly initialized.
//
// `SUCCESS_ANOTHER` indicates that another character should be passed to the
// lexer. The result has been properly initialized.
typedef enum e_ms_lex_r
{
	MS_LEX_R_FAILURE,
	MS_LEX_R_INCOMPLETE,
	MS_LEX_R_SUCCESS_SAME,
	MS_LEX_R_SUCCESS_ANOTHER,
}	t_ms_lex_r;

// Parses an additional byte in order to produce a token.
t_ms_lex_r	ms_lexer_absorbe(t_ms_lexer *self, char c, t_ms_tok *res);

#endif
