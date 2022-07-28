/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_ast_show.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 10:16:21 by nmathieu          #+#    #+#             */
/*   Updated: 2022/07/04 17:20:42 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms/parse/ast.h"
#include "ms/utils/io.h"
#include <unistd.h>
#include <stdint.h>

static void	inner(t_ms_ast *ast, size_t depth);

static const char	*g_ast_names[] = {
	"[CMD]",
	"[PIPE]",
	"[AND_IF]",
	"[OR_IF]",
	"[SEQ]",
	"[SUBSH]",
};

static void	put_binop(struct s_ms_ast_binop *binop, size_t depth)
{
	write(STDOUT_FILENO, "\n", 1);
	inner(binop->left, depth + 1);
	inner(binop->right, depth + 1);
}

static void	put_subsh(struct s_ms_ast_subsh *subsh, size_t depth)
{
	size_t	i;

	i = 0;
	while (i < subsh->iord_count)
		ms_iord_show(&subsh->iords[i++]);
	write(STDOUT_FILENO, "\n", 1);
	inner(subsh->root, depth + 1);
}

static void	inner(t_ms_ast *ast, size_t depth)
{
	size_t	i;

	if (!ast)
	{
		write(STDOUT_FILENO, "[NULL]\n", 7);
		return ;
	}
	i = 0;
	while (i++ < depth)
		write(STDOUT_FILENO, "    ", 4);
	ms_putstr(g_ast_names[ast->kind]);
	if (ast->kind == MS_AST_CMD)
	{
		ms_command_show(&ast->cmd);
		write(STDOUT_FILENO, "\n", 1);
	}
	else if (ast->kind == MS_AST_PIPE || ast->kind == MS_AST_AND_IF
		|| ast->kind == MS_AST_OR_IF || ast->kind == MS_AST_SEQ)
		put_binop(&ast->binop, depth);
	else if (ast->kind == MS_AST_SUBSH)
		put_subsh(&ast->subsh, depth);
}

void	ms_ast_show(t_ms_ast *ast)
{
	inner(ast, 0);
}
