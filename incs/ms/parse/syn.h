/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syn.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 22:46:40 by nmathieu          #+#    #+#             */
/*   Updated: 2022/07/04 17:08:39 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYN_H
# define SYN_H

# include "ms/parse/ast.h"

// The kind of a `t_ms_syn` element.
typedef enum e_ms_syn_kind
{
	MS_SYN_END,
	MS_SYN_CMD,
	MS_SYN_AND_IF,
	MS_SYN_OR_IF,
	MS_SYN_PIPE,
	MS_SYN_SEQ,
	MS_SYN_OPAREN,
	MS_SYN_CPAREN,
}	t_ms_syn_kind;

// An syntactical element.
typedef struct s_ms_syn
{
	t_ms_syn_kind	kind;
	union
	{
		t_ms_command	cmd;
		struct s_ms_syn_cparen
		{
			t_ms_iord	*iords;
			size_t		iord_count;
		}	cparen;
	};
}	t_ms_syn;

// Frees the resources allocated for a `t_ms_syn` instance.
void	ms_syn_free(t_ms_syn *self);

// Displays the provide `t_ms_syn` instance on the standard output.
void	ms_syn_show(t_ms_syn *self);

#endif
