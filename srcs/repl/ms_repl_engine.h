/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_repl_engine.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 12:06:37 by nmathieu          #+#    #+#             */
/*   Updated: 2022/07/25 20:20:22 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_REPL_ENGINE_H
# define MS_REPL_ENGINE_H

# include "ms/parse/parser.h"
# include "ms/parse/lexer.h"
# include "ms/parse/syner.h"
# include <stdbool.h>

// Stores the state required by the in order to generate command trees from the
// lines provided by the user.
typedef struct s_ms_repl_engine
{
	t_ms_lexer	lexer;
	t_ms_syner	syner;
	t_ms_parser	parser;

	bool		reuse_token;
	t_ms_tok	token;

	struct s_ms_repl_engine_here_docs
	{
		char	*buf;
		size_t	cap;
		size_t	len;
		char	*delim;
	}	here_doc;
	bool		first_prompt;

	struct s_ms_repl_engine_cmd
	{
		char	*buf;
		size_t	cap;
		size_t	len;
	}	cmd_buf;
}	t_ms_repl_engine;

// Initializes a `t_ms_repl_engine` instance.
bool	ms_repl_engine_init(t_ms_repl_engine *self);

// Frees the resources allocated for a `t_ms_repl_engine` instance.
void	ms_repl_engine_deinit(t_ms_repl_engine *self);

void	ms_repl_engine_reset(t_ms_repl_engine *self);

// Provides an additional line to the `t_ms_repl_engine` instance.
//
// -1   - An unexpected error occured.
//  0   - Additional lines are required.
//  1   - An AST has been generated.
int		ms_repl_engine_absorbe(
			t_ms_repl_engine *self,
			char *line,
			t_ms_ast **ast);

int		ms_repl_engine_absorbe_char(
			t_ms_repl_engine *self,
			char c,
			t_ms_ast **ast,
			bool *reuse_char);

#endif
