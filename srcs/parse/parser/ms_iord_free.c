/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_iord_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 12:42:51 by nmathieu          #+#    #+#             */
/*   Updated: 2022/07/04 11:37:20 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms/parse/ast.h"
#include <stdlib.h>
#include <stdbool.h>

void	ms_iord_free(t_ms_iord *self)
{
	if (false
		|| self->kind == MS_IORD_APPEND
		|| self->kind == MS_IORD_READ
		|| self->kind == MS_IORD_WRITE)
		free(self->filename);
	else if (self->kind == MS_IORD_HERE_DOC)
	{
		free(*self->here_doc.contents);
		free(self->here_doc.contents);
	}
}
