/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 13:06:14 by damateos          #+#    #+#             */
/*   Updated: 2024/02/04 14:25:13 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* Resizes the buffer to the new_size or initializes it if NULL */
char	*resize_buff(char *buff, size_t new_size)
{
	char	*temp;
	size_t	i;

	temp = malloc(new_size);
	if (!temp)
	{
		free(buff);
		buff = NULL;
		return (NULL);
	}
	i = -1;
	while (buff[++i])
		temp[i] = buff[i];
	if (buff)
		free(buff);
	buff = temp;
	return (buff);
}

int	get_newline_i(const char *s, int lim)
{
	int	i;

	i = 0;
	while (i < lim)
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}
// "abc0"
int	read_chunk(char *buff, size_t len, size_t buff_size, int fd)
{
	size_t	read_b;
	int		newline_i;

	buff = resize_buff(buff, len + buff_size);
	if (!buff)
		return (-1);
	read_b = read(fd, buff + len, buff_size);
	if (read_b == -1)
	{
		free(buff);
		return (-1);
	}
	if (read_b < buff_size)
	{
		resize_buff(buff, len + read_b);
		if (!buff)
			return (-1);
		return (1);
	}
	newline_i = get_newline_i(buff, len + buff_size);
	if (newline_i != -1)
	{
		resize_buff(buff, len + newline_i + 1);
		if (!buff)
			return (-1);
		return (1);
	}
	return (0);
}
/*
 * read_chunk:
 * increases buffer by buffer size and fills it
 * if memory allocation or read fails, returns -1
 * if found new_line or eof, returns 1,
 * otherwise, returns 0,
 */
