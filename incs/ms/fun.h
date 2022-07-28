/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fun.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 20:07:43 by nmathieu          #+#    #+#             */
/*   Updated: 2022/06/26 17:00:44 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUN_H
# define FUN_H

# include <stdbool.h>

// Prints the tokens found in the provided file descriptor.
bool	ms_show_tokens(int fd);

// Prints a fully expanded version of the commands in the provided file
// descriptor.
bool	ms_show_expanded(int fd);

// Prints the syntax elements generated from the commands in the provided
// file.
bool	ms_show_syntax(int fd);

// Prints the Abstract Syntax Tree generated from the commands in the provided
// file.
bool	ms_show_ast(int fd);

// Executes the provided file.
bool	ms_execute(int fd);

// Starts the Read-Execute-Parse-Loop.
bool	ms_repl_entry_point(void);

#endif
