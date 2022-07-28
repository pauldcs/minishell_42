/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_str_starts_with.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:01:24 by nmathieu          #+#    #+#             */
/*   Updated: 2022/06/01 14:02:27 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

bool	ms_str_starts_with(const char *haystack, const char *needle)
{
	while (*haystack && *needle && *needle == *haystack)
	{
		haystack++;
		needle++;
	}
	return (*needle == '\0');
}
