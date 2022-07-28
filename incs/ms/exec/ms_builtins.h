/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtins.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 12:30:56 by pducos            #+#    #+#             */
/*   Updated: 2022/07/26 11:37:37 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_BUILTINS_H
# define MS_BUILTINS_H

int		ms_pwd(char **args, char **envp);
int		ms_cd(char **args, char **envp);
int		ms_echo(char **args, char **envp);
int		ms_exit(char **args, char **envp);
int		ms_env(char **args, char **envp);
int		ms_unset(char **args, char **envp);
int		ms_export(char **args, char **envp);

#endif
