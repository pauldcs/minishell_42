/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_ast_precedence.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 14:20:37 by nmathieu          #+#    #+#             */
/*   Updated: 2022/06/30 10:42:15 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms/parse/ast.h"

static const int	g_lookup[] = {
	-1,
	1,
	2,
	2,
	3,
	4,
};

int	ms_ast_precedence(t_ms_ast_kind kind)
{
	return (g_lookup[kind]);
}
