/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_ast_reader_next.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 17:59:33 by nmathieu          #+#    #+#             */
/*   Updated: 2022/06/28 17:31:33 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms/parse/ast_reader.h"
#include "ms/state.h"

int	ms_ast_reader_next(t_ms_ast_reader *self, t_ms_ast **result)
{
	int			ret;
	t_ms_syn	syn;

	while (true)
	{
		ret = ms_syn_reader_next(&self->syn_reader, &syn);
		if (ret == -1)
			return (false);
		if (ret == 0)
		{
			self->exhausted = true;
			return (0);
		}
		ret = ms_parser_absorbe(&self->parser, &syn, result);
		if (ret == MS_PARSE_R_FAILURE)
			return (-1);
		if (ret == MS_PARSE_R_SUCCESS)
		{
			ms_syner_send_here_docs(&self->syn_reader.syner);
			return (1);
		}
	}
}
