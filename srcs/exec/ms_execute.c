/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 16:31:49 by nmathieu          #+#    #+#             */
/*   Updated: 2022/07/11 12:26:36 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms/parse/ast_reader.h"
#include "ms/parse/ast.h"
#include "ms/exec.h"
#include <stdbool.h>

bool	ms_execute(int fd)
{
	t_ms_ast_reader	reader;
	int				ret;
	t_ms_ast		*ast;

	if (!ms_ast_reader_init(&reader, fd))
		return (false);
	while (true)
	{
		ret = ms_ast_reader_next(&reader, &ast);
		if (ret == -1)
			return (ms_ast_reader_deinit(&reader), false);
		if (ret == 0)
			return (ms_ast_reader_deinit(&reader), true);
		if (ast && !ms_execute_ast(ast))
			return (ms_ast_reader_deinit(&reader), false);
		ms_ast_free(ast);
	}
}
