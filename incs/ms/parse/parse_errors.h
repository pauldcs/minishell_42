/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_errors.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 15:44:59 by nmathieu          #+#    #+#             */
/*   Updated: 2022/06/26 16:12:02 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_ERRORS_H
# define PARSE_ERRORS_H

# include <stddef.h>
# include "ms/parse/token.h"

void	ms_parse_err_token(size_t line, t_ms_tok *tok);
void	ms_parse_err_token_err(size_t line, t_ms_tok *tok);
void	ms_parse_err_here_doc(size_t line, char *delim);

#endif
