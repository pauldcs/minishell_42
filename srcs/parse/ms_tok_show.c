/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tok_show.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 10:08:00 by nmathieu          #+#    #+#             */
/*   Updated: 2022/07/04 12:23:44 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms/parse/token.h"
#include "ms/utils/io.h"
#include <unistd.h>
#include <stdint.h>

static const t_ms_str	g_names[] = {
{"EOF", 3},
{"NEWLINE", 7},
{"WORD", 4},
{"DAND", 4},
{"OR", 2},
{"DOR", 3},
{"LESS", 4},
{"DLESS", 5},
{"GREAT", 5},
{"DGREAT", 6},
{"OPAREN", 6},
{"CPAREN", 6},
};

static const t_ms_str	g_errs[] = {
{"ERR_NOSQUOTE", 12},
{"ERR_NODQUOTE", 12},
};

void	ms_tok_show(t_ms_tok *token)
{
	if (token->kind & MS_TOK_ERR_MASK)
	{
		token->kind &= ~MS_TOK_ERR_MASK;
		write(STDOUT_FILENO, g_errs[token->kind].s, g_errs[token->kind].len);
		write(STDOUT_FILENO, "\n", 1);
	}
	else
	{
		write(STDOUT_FILENO, g_names[token->kind].s, g_names[token->kind].len);
		write(STDOUT_FILENO, " (", 2);
		ms_putdstr(token->slice);
		write(STDOUT_FILENO, ")\n", 2);
	}
}
