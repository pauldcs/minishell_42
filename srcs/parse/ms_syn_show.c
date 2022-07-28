/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_syn_show.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 10:14:02 by nmathieu          #+#    #+#             */
/*   Updated: 2022/07/04 17:11:48 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms/parse/syn.h"
#include "ms/utils/io.h"
#include <unistd.h>
#include <stdint.h>
#include "ms/utils/mem.h"
#include "ms/parse/expand.h"
#include <stdlib.h>

static const char	*g_syn_names[] = {
	"[END]",
	"[CMD]",
	"[AND_IF]",
	"[OR_IF]",
	"[PIPE]",
	"[SEQ]",
	"[OPAREN]",
	"[CPAREN]",
};

static void	print_iords(t_ms_iord *iords, size_t count)
{
	while (count)
	{
		ms_iord_show(iords);
		iords++;
		count--;
	}
}

void	ms_syn_show(t_ms_syn *syn)
{
	ms_putstr(g_syn_names[syn->kind]);
	if (syn->kind == MS_SYN_CMD)
		ms_command_show(&syn->cmd);
	if (syn->kind == MS_SYN_CPAREN)
		print_iords(syn->cparen.iords, syn->cparen.iord_count);
	write(STDOUT_FILENO, "\n", 1);
}
