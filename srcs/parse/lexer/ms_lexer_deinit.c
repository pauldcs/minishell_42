/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer_deinit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 23:18:16 by nmathieu          #+#    #+#             */
/*   Updated: 2022/06/09 14:02:23 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms/parse/lexer.h"
#include <stdlib.h>

void	ms_lexer_deinit(t_ms_lexer *self)
{
	if (self->chars.cap != 0)
		free(self->chars.buf);
}
