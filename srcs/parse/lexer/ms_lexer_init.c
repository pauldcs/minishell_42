/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 17:33:03 by nmathieu          #+#    #+#             */
/*   Updated: 2022/06/09 14:02:10 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms/parse/lexer.h"
#include <stdlib.h>

void	ms_lexer_init(t_ms_lexer *self)
{
	self->state = MS_LEX_INIT;
	self->chars.buf = NULL;
	self->chars.len = 0;
	self->chars.cap = 0;
}
