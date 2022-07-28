/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:23:18 by nmathieu          #+#    #+#             */
/*   Updated: 2022/07/26 11:31:07 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATE_H
# define STATE_H

# include "ms/utils/str.h"
# include <stdbool.h>
# include <stddef.h>
# include <sys/types.h>
# include "ms/parse/command.h"

typedef enum e_ms_state_mode
{
	MS_STATE_REPL,
	MS_STATE_SHOW_TOKENS,
	MS_STATE_SHOW_EXPANDED,
	MS_STATE_SHOW_SYNTAX,
	MS_STATE_SHOW_AST,
	MS_STATE_EXECUTE,
}	t_ms_state_mode;

// A shell variable.
typedef struct s_ms_var
{
	char	*name;
	char	*value;
	bool	exported;
}	t_ms_var;

typedef struct s_ms_vars
{
	t_ms_var	*buf;
	size_t		cap;
	size_t		len;
}	t_ms_vars;

// The state of the shell. An instance of this type is kept as a global and is
// accessible from the whole application.
typedef struct s_ms_state
{
	const char	*exec_name;

	bool		exit_called;
	int			status;

	t_ms_vars	vars;

	int			stdin;
	int			stdout;
	int			stderr;
	bool		interrupted;
}	t_ms_state;

// The global state of the execution.
extern t_ms_state	g_ms;

// Initializes the `g_ms` global variable.
bool		ms_init_state(const char *exec_name, char **envp);

// Frees the resources allocated for the global variable.
void		ms_deinit_state(void);

// Initializes a `t_ms_var` instance.
void		ms_var_init(t_ms_var *self, char *name, char *value, bool exported);

// Frees the resources allocated for a `t_ms_var` instance.
void		ms_var_deinit(t_ms_var *self);

/// Sets the value of a shell variable.
bool		ms_var_set(t_ms_vars *self, char *name, char *value, bool export);
bool		ms_var_append(
				t_ms_vars *self, char *name, char *value, bool export);
bool		ms_var_assign(t_ms_vars *self, t_ms_assign assign, bool export);

bool		ms_var_remove(t_ms_vars *self, const char *name);

bool		ms_var_setup(
				t_ms_vars *self,
				const char *name,
				const char *values,
				bool export);

// Returns the value of the specified variable.
const char	*ms_var_get(t_ms_vars *self, t_ms_str name);

// Returns the environment that should be passed to commands.
char		**ms_var_env(t_ms_vars *self, t_ms_assign *os, size_t *count);

bool		ms_vars_parse(t_ms_vars *self, char **envp);

bool		ms_sigset_prompt(void);
bool		ms_sigset_prompt2(void);
bool		ms_sigset_command(void);
bool		ms_sigset_default(void);

#endif
