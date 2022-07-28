/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_show_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 15:09:35 by nmathieu          #+#    #+#             */
/*   Updated: 2022/06/17 10:11:17 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms/utils/str.h"
#include "ms/utils/io.h"
#include "ms/parse/token.h"
#include "ms/parse/lexer.h"
#include "ms/parse/tok_reader.h"

bool	ms_show_tokens(int fd)
{
	t_ms_tok_reader	reader;
	t_ms_tok		token;
	int				ret;

	ms_tok_reader_init(&reader, fd);
	while (true)
	{
		ret = ms_tok_reader_next(&reader, &token);
		if (ret == -1)
			return (ms_tok_reader_deinit(&reader), false);
		if (ret == 0)
			return (ms_tok_reader_deinit(&reader), true);
		ms_tok_show(&token);
	}
}
