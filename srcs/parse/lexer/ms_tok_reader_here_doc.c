/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tok_reader_here_doc.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 13:34:42 by nmathieu          #+#    #+#             */
/*   Updated: 2022/06/27 21:59:14 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms/parse/tok_reader.h"
#include "ms/utils/alloc.h"
#include "ms/utils/mem.h"
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>

static bool	read_one(t_ms_tok_reader *self, char *byte)
{
	ssize_t	count;

	if (self->cur == self->init)
	{
		count = read(self->fd, self->buf, MS_TOK_READER_BUF_SIZE);
		if (count < 0)
			return (false);
		self->cur = 0;
		self->init = count;
		if (count == 0)
		{
			*byte = '\0';
			return (true);
		}
	}
	*byte = self->buf[self->cur];
	self->cur++;
	return (true);
}

static int	is_finished(
				t_ms_vec *buf,
				char *delim,
				t_ms_str *contents,
				size_t *found)
{
	if (*found == SIZE_MAX)
		return (0);
	if (delim[*found] == '\0'
		&& (((char *)buf->buf)[buf->len] == '\n'
		|| ((char *)buf->buf)[buf->len] == '\0'))
	{
		*contents = (t_ms_str){buf->buf, buf->len - *found};
		if (((char *)buf->buf)[buf->len] == '\n')
			return (1);
		else
			return (2);
	}
	if (delim[*found] == ((char *)buf->buf)[buf->len])
		(*found)++;
	else
		*found = SIZE_MAX;
	return (0);
}

int	ms_tok_reader_here_doc(
			t_ms_tok_reader *self,
			char *delim,
			t_ms_str *contents)
{
	t_ms_vec	buf;
	size_t		found;
	int			ret;

	ms_mem_set(&buf, 0x00, sizeof(t_ms_vec));
	found = 0;
	while (true)
	{
		if (!ms_vec_reserve(&buf, 1, sizeof(char))
			|| !read_one(self, buf.buf + buf.len))
			return (free(buf.buf), -1);
		ret = is_finished(&buf, delim, contents, &found);
		if (found != SIZE_MAX && (ret == 1 || ret == 2))
			return (ret);
		if (((char *)buf.buf)[buf.len] == '\0')
		{
			*contents = (t_ms_str){buf.buf, buf.len};
			return (3);
		}
		else if (((char *)buf.buf)[buf.len] == '\n')
			found = 0;
		buf.len++;
	}
}
