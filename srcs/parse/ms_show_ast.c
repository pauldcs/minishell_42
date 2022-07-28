/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_show_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 16:30:05 by nmathieu          #+#    #+#             */
/*   Updated: 2022/06/17 10:21:12 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms/parse/ast_reader.h"
#include "ms/parse/ast.h"
#include "ms/utils/io.h"
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

bool	ms_show_ast(int fd)
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
			break ;
		ms_ast_show(ast);
		ms_ast_free(ast);
	}
	return (ms_ast_reader_deinit(&reader), true);
}
