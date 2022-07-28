/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 20:16:08 by nmathieu          #+#    #+#             */
/*   Updated: 2022/07/12 18:41:26 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STR_H
# define STR_H

# include <stdbool.h>
# include <stddef.h>

// A string reference that knows its length.
//
// Note that such a string may or may not be null-terminated.
typedef struct s_ms_str
{
	const char	*s;
	size_t		len;
}	t_ms_str;

// Compares `a` and `b`.
int			ms_str_cmp(const char *a, const char *b);

// Determines whether `haystack` starts with the substring `needle`.
bool		ms_str_starts_with(const char *haystack, const char *needle);

// Allocates a null-terminated string from the provided `t_ms_str` instance.
char		*ms_str_create(const char *s, size_t len);

// Returns the length of `s`.
size_t		ms_str_len(const char *s);

// concatete two strings
char		*ms_str_cat(char *dest, char *src);

//search char 'c' in string 's'
char		*ms_str_chr(const char *s, int c);

// duplicate string 'str' of size 'size'
char		*ms_str_dup(const char *str);

// split string according to separator 'c'
char		**ms_str_split(char const *s, char c);

// sum of the length of 'n' strings
size_t		ms_strs_len(size_t n, ...);

char		*ms_save_str(const char *str);

// Copies `src` into `dst`.
//
// Returns the pointer to the null character within `dst`.
char		*ms_str_copy(char *dst, const char *src);

t_ms_str	ms_str_new(const char *s);

bool		ms_str_append(char **self, const char *str);

#endif
