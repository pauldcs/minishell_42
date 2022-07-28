/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_reader.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 23:23:13 by nmathieu          #+#    #+#             */
/*   Updated: 2022/06/27 20:46:19 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOK_READER_H
# define TOK_READER_H

# include "ms/parse/lexer.h"

// The size of the `read` calls performed by a `t_ms_tok_reader` instance.
# define MS_TOK_READER_BUF_SIZE 4096

// Stores the state required to read tokens from a file descriptor.
typedef struct s_ms_tok_reader
{
	int			fd;
	char		buf[MS_TOK_READER_BUF_SIZE];
	size_t		cur;
	size_t		init;
	bool		exhausted;
	t_ms_lexer	lexer;
	size_t		line;
}	t_ms_tok_reader;

// Initializes a `t_ms_tok_reader` instance.
void	ms_tok_reader_init(t_ms_tok_reader *self, int fd);

// Frees the resources allocated for a token reader.
void	ms_tok_reader_deinit(t_ms_tok_reader *self);

// Reads another token from the provided `t_ms_tok_reader`.
//
// -1 - An error occured whilst reading the file.
// 0  - No more token are to be expected. `result` is left undefined.
// 1  - More tokens on the way!
int		ms_tok_reader_next(t_ms_tok_reader *self, t_ms_tok *result);

// Reads a single here-document.
//
// -1  - An error occured.
//  1  - The here document was properly parsed.
//  2  - The here document was properly parsed and OEF was found.
//  3  - The here documeht was found but without a delimiter.
int		ms_tok_reader_here_doc(
			t_ms_tok_reader *self,
			char *delim,
			t_ms_str *contents);

#endif
