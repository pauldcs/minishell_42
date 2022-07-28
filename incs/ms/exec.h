/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pducos <pducos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 16:34:09 by nmathieu          #+#    #+#             */
/*   Updated: 2022/07/07 18:19:15 by pducos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "ms/parse/ast.h"
# include "ms/parse/expand.h"
# include <stdbool.h>

// Executes the provided AST.
bool	ms_execute_ast(t_ms_ast *ast);
bool	ms_execute_expast(t_ms_expast *ast);
int		execute(t_ms_ast *ast);

#endif
