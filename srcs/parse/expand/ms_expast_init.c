/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expast_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 18:17:28 by nmathieu          #+#    #+#             */
/*   Updated: 2022/07/25 20:51:34 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms/parse/expand.h"
#include "ms/utils/str.h"
#include <stdlib.h>

bool	ms_init_vars(t_ms_assign **ret, t_ms_assign *vars, size_t count);

static void	free_args_array(char **args)
{
	size_t	i;

	i = 0;
	while (args[i])
		free(args[i++]);
	free(args);
}

static void	free_iords(t_ms_expiord *iords, size_t count)
{
	size_t	i;

	if (count)
	{
		i = 0;
		while (i < count)
			ms_expiord_deinit(&iords[i++]);
		free(iords);
	}
}

static bool	ms_expast_cmd_init(
				struct s_ms_expast_cmd *self,
				const t_ms_command *cmd)
{
	self->args = ms_expand_args(cmd->args, cmd->arg_count);
	if (!self->args)
		return (false);
	if (!ms_expiord_array_init(&self->iords, cmd->iords, cmd->iord_count))
		return (free_args_array(self->args), false);
	self->iord_count = cmd->iord_count;
	if (!ms_init_vars(&self->overrides, cmd->overrides, cmd->override_count))
		return (free_args_array(self->args),
			free_iords(self->iords, self->iord_count), false);
	self->override_count = cmd->override_count;
	return (true);
}

static bool	ms_expast_subsh_init(
	struct s_ms_expast_subsh *self,
	const struct s_ms_ast_subsh *subsh)
{
	if (!ms_expiord_array_init(&self->iords, subsh->iords, subsh->iord_count))
		return (false);
	self->iord_count = subsh->iord_count;
	self->root = subsh->root;
	return (true);
}

bool	ms_expast_init(t_ms_expast *self, const t_ms_ast *ast)
{
	self->kind = ast->kind;
	if (ast->kind == MS_AST_CMD)
		return (ms_expast_cmd_init(&self->cmd, &ast->cmd));
	else if (ast->kind == MS_AST_SUBSH)
		return (ms_expast_subsh_init(&self->subsh, &ast->subsh));
	else
	{
		self->binop.left = ast->binop.left;
		self->binop.right = ast->binop.right;
		return (true);
	}
}
