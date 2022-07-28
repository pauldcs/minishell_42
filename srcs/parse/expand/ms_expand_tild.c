/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_tild.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 11:38:00 by nmathieu          #+#    #+#             */
/*   Updated: 2022/07/25 20:42:18 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stddef.h>
#include "ms/utils/str.h"
#include "ms/state.h"
#include "ms/utils/io.h"
#include "ms/utils/alloc.h"

char	*ms_expand_tild(const char *word)
{
	char		*ret;
	size_t		len;
	const char	*home;

	if (word[0] != '~'
		|| (word[1] != ':' && word[1] != '/' && word[1]))
		return (ms_str_dup(word));
	home = ms_var_get(&g_ms.vars, (t_ms_str){"HOME", 4});
	if (!home)
		return (ms_error("%s: no $HOME found"), NULL);
	len = ms_str_len(word) - 1 + ms_str_len(home);
	ret = ms_alloc(len + 1);
	if (!ret)
		return (false);
	ms_str_copy(ms_str_copy(ret, home), word + 1);
	return (ret);
}
