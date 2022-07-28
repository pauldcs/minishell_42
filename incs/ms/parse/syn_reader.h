/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syn_reader.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 01:38:11 by nmathieu          #+#    #+#             */
/*   Updated: 2022/06/11 14:45:10 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYN_READER_H
# define SYN_READER_H

# include "ms/parse/syner.h"
# include "ms/parse/tok_reader.h"
# include <stddef.h>
# include <stdbool.h>

// Stores the state required to read `t_ms_syn` instances from a file.
typedef struct s_ms_syn_reader
{
	t_ms_tok_reader	tokens;
	t_ms_syner		syner;

	bool			reuse_token;
	t_ms_tok		last_token;

	bool			exhausted;
}	t_ms_syn_reader;

// Initializes the provided `t_ms_syn_reader` instance.
void	ms_syn_reader_init(t_ms_syn_reader *self, int fd);

// Frees the resources allocated for a `t_ms_syn_reader`.
void	ms_syn_reader_deinit(t_ms_syn_reader *self);

// Get another `t_ms_syn` instance.
int		ms_syn_reader_next(t_ms_syn_reader *self, t_ms_syn *syn);

#endif
