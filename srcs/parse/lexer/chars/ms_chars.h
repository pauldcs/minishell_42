/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_chars.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 23:23:03 by nmathieu          #+#    #+#             */
/*   Updated: 2022/06/01 12:46:28 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_CHARS_H
# define MS_CHARS_H

# include <stdbool.h>

bool	ms_ischar(char c);
bool	ms_islower(char c);
bool	ms_isupper(char c);
bool	ms_isalpha(char c);
bool	ms_isdigit(char c);
bool	ms_isalphanum(char c);
bool	ms_isspace(char c);
bool	ms_isnull(char c);
bool	ms_iseol(char c);
bool	ms_isand(char c);
bool	ms_isor(char c);
bool	ms_isless(char c);
bool	ms_isgreat(char c);
bool	ms_ispunct(char c);
bool	ms_isdollar(char c);
bool	ms_isquestion(char c);
bool	ms_isunderscore(char c);
bool	ms_issquote(char c);
bool	ms_isdquote(char c);
bool	ms_isbackslash(char c);
bool	ms_isoparen(char c);
bool	ms_iscparen(char c);

#endif
