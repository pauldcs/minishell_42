/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 11:00:24 by nmathieu          #+#    #+#             */
/*   Updated: 2022/07/26 10:37:09 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "ms/utils/alloc.h"
# include "ms/utils/str.h"
# include "ms/parse/command.h"
# include "ms/parse/ast.h"
# include <stdbool.h>
# include <stddef.h>

char	*ms_expand_vars(const char *arg);

// Perform the "quote removal" operation on the provided word.
//
// This function returns whether removal occured.
bool	ms_remove_quotes(char *word);

// Pushes the provided word, expanded, in the vector.
bool	ms_push_expanded(char *word, t_ms_vec *vec);

// Splits `word` into multiple words and pushes them to the provided vector.
bool	ms_split_fields(t_ms_vec *vec, char *word);

// Expands wilecards within the provided word.
bool	ms_expand_pathname(t_ms_vec *vec, char *word, bool *worked);

char	*ms_expand_tild(const char *word);

char	**ms_expand_args(char **args, size_t count);

char	*ms_expand_filename(char *word);

typedef struct t_ms_expiord
{
	t_ms_iord_kind	kind;

	int				fd;

	union
	{
		char		*filename;
		char		*here_doc;
	};
}	t_ms_expiord;

bool	ms_expiord_init(t_ms_expiord *self, const t_ms_iord *iord);
void	ms_expiord_deinit(t_ms_expiord *self);
bool	ms_expiord_array_init(t_ms_expiord **ret, t_ms_iord *iords, size_t c);

typedef struct t_ms_expast
{
	t_ms_ast_kind	kind;

	union
	{
		struct s_ms_expast_cmd
		{
			char			**args;

			t_ms_expiord	*iords;
			size_t			iord_count;

			t_ms_assign		*overrides;
			size_t			override_count;
		}	cmd;
		struct s_ms_expast_binop
		{
			t_ms_ast	*left;
			t_ms_ast	*right;
		}	binop;
		struct s_ms_expast_subsh
		{
			t_ms_ast		*root;

			t_ms_expiord	*iords;
			size_t			iord_count;
		}	subsh;
	};
}	t_ms_expast;

// Converts an `ast` instance into an `expast`.
//
// Note that the resulting `expast` must be deinitialized using the
// `ms_expast_deinit` function *before* the provided `t_ms_ast` is freed.
bool	ms_expast_init(t_ms_expast *self, const t_ms_ast *ast);

void	ms_expast_deinit(t_ms_expast *self);

typedef struct s_star_exp
{
	t_ms_vec	*vec;
	char		*path;
	char		*pathname;
}	t_star_exp;

#endif
