/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_show_syntax.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 16:30:05 by nmathieu          #+#    #+#             */
/*   Updated: 2022/06/17 10:14:59 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms/parse/syn_reader.h"
#include "ms/parse/syn.h"
#include "ms/utils/io.h"
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>

bool	ms_show_syntax(int fd)
{
	t_ms_syn_reader	reader;
	int				ret;
	t_ms_syn		syn;

	ms_syn_reader_init(&reader, fd);
	while (true)
	{
		ret = ms_syn_reader_next(&reader, &syn);
		if (ret == -1)
			return (ms_syn_reader_deinit(&reader), false);
		if (ret == 0)
			return (ms_syn_reader_deinit(&reader), true);
		ms_syn_show(&syn);
		ms_syn_free(&syn);
	}
}
