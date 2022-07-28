/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syner.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 22:55:24 by nmathieu          #+#    #+#             */
/*   Updated: 2022/07/13 22:49:56 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYNER_H
# define SYNER_H

# include "ms/parse/syn.h"
# include "ms/parse/token.h"
# include "ms/parse/expand.h"
# include <stdbool.h>
# include <stddef.h>

// The state a `t_ms_syner` instance can be in.
typedef enum e_ms_syner_state
{
	MS_SYNER_INIT,
	MS_SYNER_COMMAND,
	MS_SYNER_COMMAND_END,
	MS_SYNER_CMD_READ,
	MS_SYNER_CMD_WRITE,
	MS_SYNER_CMD_APPEND,
	MS_SYNER_CMD_HERE_DOC,
	MS_SYNER_OPAREN,
	MS_SYNER_CPAREN,
	MS_SYNER_CPAR_READ,
	MS_SYNER_CPAR_WRITE,
	MS_SYNER_CPAR_APPEND,
	MS_SYNER_CPAR_HERE_DOC,
	MS_SYNER_AND_IF,
	MS_SYNER_OR_IF,
	MS_SYNER_PIPE,
	MS_SYNER_SEQ,
}	t_ms_syner_state;

typedef struct s_ms_here_doc
{
	char	*delim;
	char	*contents;
	char	**target;
}	t_ms_here_doc;

// Stores the state of the syntaxic analyzer.
typedef struct s_ms_syner
{
	t_ms_syner_state	state;
	size_t				depth;

	struct s_ms_syner_iords
	{
		t_ms_iord		*buf;
		size_t			cap;
		size_t			len;
	}	iords;
	struct s_ms_syner_args
	{
		char			**buf;
		size_t			cap;
		size_t			len;
	}	args;
	struct s_ms_syner_vars
	{
		t_ms_assign		*buf;
		size_t			cap;
		size_t			len;
	}	vars;
	struct s_ms_syner_here_docs
	{
		t_ms_here_doc	*buf;
		size_t			cap;
		size_t			len;
		size_t			complete;
	}	here_docs;
}	t_ms_syner;

// Initializes a `t_ms_syner` instance.
void		ms_syner_init(t_ms_syner *self);

// Deinitializes a `t_ms_syner` instance.
void		ms_syner_deinit(t_ms_syner *self);

char		*ms_syner_here_doc(t_ms_syner *self);

bool		ms_syner_submit_here_doc(t_ms_syner *self, t_ms_str contents);

void		ms_syner_send_here_docs(t_ms_syner *self);

// The result of the syntactical analysis performed in `ms_syner_absorbe`.
typedef enum e_ms_syn_r
{
	MS_SYN_R_SUCCESS_CONSUME,
	MS_SYN_R_SUCCESS_PRESERVE,
	MS_SYN_R_FAILURE,
	MS_SYN_R_INCOMPLETE,
	MS_SYN_R_UNEXPECTED_TOKEN,
}	t_ms_syn_r;

// Absorbes a new token.
t_ms_syn_r	ms_syner_absorbe(
				t_ms_syner *self,
				t_ms_tok *token,
				t_ms_syn *result);

#endif
