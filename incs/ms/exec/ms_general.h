/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_general.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pducos <pducos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 08:56:59 by pducos            #+#    #+#             */
/*   Updated: 2022/07/03 13:26:07 by pducos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_GENERAL_H
# define MS_GENERAL_H

# include <stdbool.h>

# define F_EXISTS		0x01
# define F_DIRECTORY	0x02
# define F_EXECABLE		0x04
# define F_READABLE		0x08

int		ms_file_status(const char *name);
int		ms_file_exists(const char *file);
int		ms_file_is_execable(const char *file);
int		ms_file_is_writable(const char *file);
int		ms_file_is_readable(const char *file);
int		ms_file_is_directory(const char *file);
char	*ms_current_working_directory(void);
bool	ms_is_builtin(char *name);
void	ms_fri_and_exit(int status);

#endif
