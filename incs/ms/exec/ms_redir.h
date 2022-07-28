/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redir.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 22:25:07 by pducos            #+#    #+#             */
/*   Updated: 2022/07/13 22:49:30 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_REDIR_H
# define MS_REDIR_H

# include "ms/parse/expand.h"

int	ms_do_redirections(t_ms_expiord *iords, size_t n);
int	ms_file_open(const char *filename);
int	ms_file_write(const char *filename);
int	ms_file_append(const char *filename);
int	ms_do_heredoc(char *contents);

#endif
