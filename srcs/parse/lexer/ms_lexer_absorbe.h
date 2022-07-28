/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer_absorbe.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 20:10:51 by nmathieu          #+#    #+#             */
/*   Updated: 2022/06/27 22:09:38 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_LEXER_ABSORBE_H
# define MS_LEXER_ABSORBE_H

# include "ms/parse/lexer.h"

# include <stdbool.h>

// Determines whether `c` is part of a certain class of characters.
typedef bool	(*t_ms_char_pred)(char c);

// Describes a transition between a state to another.
typedef struct s_ms_lex_trans
{
	t_ms_char_pred	charclass;
	t_ms_lex_state	state;
}	t_ms_lex_trans;

// Stores information about a lexer state that is ready to produce a token.
typedef struct s_ms_lex_final
{
	t_ms_tok_kind	kind;
	t_ms_lex_r		ret;
}	t_ms_lex_final;

#endif
