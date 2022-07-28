/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_strs_len.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pducos <pducos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:07:31 by pducos            #+#    #+#             */
/*   Updated: 2022/06/06 19:34:35 by pducos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stddef.h>
#include "ms/utils/str.h"

size_t	ms_strs_len(size_t n, ...)
{
	va_list	ap;
	size_t	len;

	len = 0;
	va_start(ap, n);
	while (n--)
		len += ms_str_len(va_arg(ap, char *));
	va_end(ap);
	return (len);
}
