/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_ast_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 12:44:50 by nmathieu          #+#    #+#             */
/*   Updated: 2022/07/08 13:21:15 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms/parse/ast.h"
#include <stdbool.h>
#include <stdlib.h>

static void	free_iords(t_ms_iord *iords, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
		ms_iord_free(&iords[i++]);
	if (len)
		free(iords);
}

static void	free_binop(struct s_ms_ast_binop *binop)
{
	ms_ast_free(binop->left);
	ms_ast_free(binop->right);
}

static void	free_subsh(struct s_ms_ast_subsh *subsh)
{
	free_iords(subsh->iords, subsh->iord_count);
	ms_ast_free(subsh->root);
}

void	ms_ast_free(t_ms_ast *self)
{
	if (!self)
		return ;
	if (false
		|| self->kind == MS_AST_AND_IF
		|| self->kind == MS_AST_OR_IF
		|| self->kind == MS_AST_PIPE
		|| self->kind == MS_AST_SEQ)
		free_binop(&self->binop);
	else if (self->kind == MS_AST_CMD)
		ms_command_free(&self->cmd);
	else if (self->kind == MS_AST_SUBSH)
		free_subsh(&self->subsh);
	free(self);
}
