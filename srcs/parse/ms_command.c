/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 17:02:12 by nmathieu          #+#    #+#             */
/*   Updated: 2022/07/25 20:50:26 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms/parse/command.h"
#include "ms/parse/expand.h"
#include "ms/utils/alloc.h"
#include "ms/utils/io.h"
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include "ms/utils/mem.h"

void	ms_command_free(t_ms_command *self)
{
	size_t	i;

	i = 0;
	while (i < self->arg_count)
		free(self->args[i++]);
	if (self->arg_count)
		free(self->args);
	i = 0;
	while (i < self->iord_count)
		ms_iord_free(&self->iords[i++]);
	if (self->iord_count)
		free(self->iords);
	i = 0;
	while (i < self->override_count)
		ms_assign_free(&self->overrides[i++]);
	if (self->override_count)
		free(self->overrides);
}

static void	print_iords(t_ms_iord *iords, size_t count)
{
	while (count)
	{
		ms_iord_show(iords);
		iords++;
		count--;
	}
}

static void	print_args(char **raw_args, size_t count)
{
	size_t		i;
	char		**args;

	args = ms_expand_args(raw_args, count);
	if (args)
	{
		i = 0;
		while (args[i])
		{
			write(STDOUT_FILENO, " '", 2);
			ms_putdstr(args[i]);
			write(STDOUT_FILENO, "'", 1);
			free(args[i]);
			i++;
		}
		free(args);
	}
}

static void	print_vars(t_ms_assign *vars, size_t count)
{
	size_t	i;
	char	*expanded;

	count && write(STDOUT_FILENO, " (", 2);
	i = 0;
	while (i < count)
	{
		write(STDOUT_FILENO, " ", 1);
		ms_putstr(vars[i].name);
		if (vars[i].append)
			write(STDOUT_FILENO, "+=", 2);
		else
			write(STDOUT_FILENO, "=", 1);
		expanded = ms_expand_vars(vars[i].value);
		if (expanded)
		{
			ms_remove_quotes(expanded);
			write(STDOUT_FILENO, "'", 1);
			ms_putstr(expanded);
			write(STDOUT_FILENO, "'", 1);
			free(expanded);
		}
		i++;
	}
	count && write(STDOUT_FILENO, " )", 2);
}

void	ms_command_show(t_ms_command *self)
{
	print_vars(self->overrides, self->override_count);
	print_iords(self->iords, self->iord_count);
	print_args(self->args, self->arg_count);
}
