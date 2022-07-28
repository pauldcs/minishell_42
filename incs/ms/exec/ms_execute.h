/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execute.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 17:46:56 by pducos            #+#    #+#             */
/*   Updated: 2022/07/13 22:49:05 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_EXECUTE_H
# define MS_EXECUTE_H

# include "ms/parse/ast.h"
# include "ms/parse/expand.h"

# define F_EXISTS	0x01
# define F_DIRECTORY	0x02
# define F_EXECABLE	0x04
# define F_READABLE	0x08
# define NO_PIPE -1

// returns full path for `name` or NULL
char	*ms_find_cmd(char *name);
void	ms_setup_subsh(t_ms_expast *ast);
void	ms_exec_builtin(t_ms_expast *ast);
int		ms_simple_command(t_ms_expast *ast);
void	ms_pipeline(t_ms_expast *ast);
void	ms_and_if(t_ms_expast *ast);
void	ms_or_if(t_ms_expast *ast);
void	ms_seq(t_ms_expast *ast);

#endif
