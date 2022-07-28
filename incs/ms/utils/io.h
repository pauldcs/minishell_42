/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 20:17:10 by nmathieu          #+#    #+#             */
/*   Updated: 2022/07/04 14:40:43 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IO_H
# define IO_H

# include <stddef.h>

// Prints `msg` to the standard output.
void	ms_putstr(const char *msg);

// Prints `msg` to the standard error.
void	ms_puterr(const char *msg);

// Prints the provied string, replacing unprintable characters by escape
// sequences.
void	ms_putdstr(const char *msg);

// Prints the provied string, replacing unprintable characters by escape
// sequences.
void	ms_putderr(const char *str);

// Prints the provided number to the standard error output.
void	ms_putnbr_err(size_t n);

int		ms_close_fd(int	*fd);

void	ms_put_sig(int sig_code);

size_t	ms_put_int(int c, int fd);

void	ms_error(const char *str, ...);

#endif
