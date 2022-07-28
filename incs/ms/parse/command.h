/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 16:59:45 by nmathieu          #+#    #+#             */
/*   Updated: 2022/07/13 22:49:45 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include <stdbool.h>
# include <stddef.h>

typedef struct s_ms_assign
{
	bool		append;
	char		*name;
	char		*value;
}	t_ms_assign;

// Parses an assignent from the provided word.
int		ms_assign_parse(t_ms_assign *result, const char *word);

void	ms_assign_free(t_ms_assign *self);

// The kind of an IO redirection.
typedef enum e_ms_iord_kind
{
	MS_IORD_HERE_DOC,
	MS_IORD_WRITE,
	MS_IORD_APPEND,
	MS_IORD_READ,
}	t_ms_iord_kind;

// An IO redirection.
typedef struct s_ms_iord
{
	t_ms_iord_kind	kind;
	int				fd;

	union
	{
		struct s_ms_iord_here_doc
		{
			char		**contents;
			bool		expand;
		}	here_doc;
		char			*filename;
	};
}	t_ms_iord;

// Frees the resources allocated for an `t_ms_iord` instance.
void	ms_iord_free(t_ms_iord *self);

// Prints a `t_ms_iord` instance to the standard output.
void	ms_iord_show(t_ms_iord *self);

typedef struct s_ms_command
{
	char		**args;
	size_t		arg_count;

	t_ms_iord	*iords;
	size_t		iord_count;

	t_ms_assign	*overrides;
	size_t		override_count;
}	t_ms_command;

void	ms_command_free(t_ms_command *self);

void	ms_command_show(t_ms_command *self);

#endif
