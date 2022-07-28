/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_iord_show.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 13:59:00 by nmathieu          #+#    #+#             */
/*   Updated: 2022/07/06 13:48:55 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms/parse/ast.h"
#include "ms/utils/io.h"
#include <unistd.h>
#include <stdint.h>
#include "ms/parse/expand.h"
#include <stdlib.h>

void	ms_parse_err_ambiguous_redirect(char *filename);

static const char	*g_iord_names[] = {
	"<<",
	">",
	">>",
	"<",
};

static void	print_here_doc(struct s_ms_iord_here_doc *here_doc)
{
	char	*expanded;

	if (*here_doc->contents)
	{
		write(STDOUT_FILENO, "'", 1);
		if (here_doc->expand)
		{
			expanded = ms_expand_vars(*here_doc->contents);
			if (expanded)
				ms_putdstr(expanded);
			free(expanded);
		}
		else
			ms_putdstr(*here_doc->contents);
		write(STDOUT_FILENO, "'", 1);
	}
	else
		ms_putstr("<uninit>");
}

static void	print_filename(char *filename)
{
	char	*expanded;

	expanded = ms_expand_filename(filename);
	if (!expanded)
		return ;
	ms_putdstr(expanded);
	free(expanded);
}

void	ms_iord_show(t_ms_iord *self)
{
	write(STDOUT_FILENO, " ", 1);
	ms_putstr(g_iord_names[self->kind]);
	write(STDOUT_FILENO, " ", 1);
	if (self->kind != MS_IORD_HERE_DOC)
		print_filename(self->filename);
	else
		print_here_doc(&self->here_doc);
}
