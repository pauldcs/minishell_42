/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 20:17:37 by nmathieu          #+#    #+#             */
/*   Updated: 2022/06/05 12:37:58 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# include <stdbool.h>

// Verifies that `condition` is `true`.
//
// If it isn't, the provided message is displayed and the program aborts.
void	ms_assert(bool condition, const char *message);

#endif
