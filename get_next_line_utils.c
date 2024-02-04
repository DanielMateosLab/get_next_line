/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 13:06:14 by damateos          #+#    #+#             */
/*   Updated: 2024/02/04 18:47:57 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* Resizes the buffer to the new_size or initializes it if NULL.
 * Null-terminates the buffer string */
void	resize_buff(char **buff, size_t len, size_t new_size)
{
	char	*temp;
	size_t	i;

	temp = malloc(new_size + 1);
	if (!temp)
	{
		free(*buff);
		*buff = NULL;
	}
	i = 0;
	while (*buff && i < len && i < new_size)
	{
		temp[i] = (*buff)[i];
		i++;
	}
	temp[new_size] = '\0';
	if (*buff)
		free(*buff);
	*buff = temp;
}

static int	get_newline_i(const char *s, int lim)
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

static int	check_success(char *buff, int res)
{
	if (!buff)
		return (-1);
	return (res);
}

/*
 * read_chunk:
 * increases buffer by buffer size and fills it reading from fd
 * if memory allocation or read fails, returns -1
 * if found new_line or eof returns 1 
 * otherwise, returns 0,
 */
int	read_chunk(char **buff, size_t len, size_t buff_size, int fd)
{
	int	read_b;
	int	newline_i;

	resize_buff(buff, len, len + buff_size);
	if (!*buff)
		return (-1);
	read_b = read(fd, *buff + len, buff_size);
	if (read_b == -1)
	{
		free(*buff);
		*buff = NULL;
		return (-1);
	}
	newline_i = get_newline_i(*buff + len, len);
	if (newline_i != -1)
	{
		resize_buff(buff, len + buff_size, len + newline_i + 1);
		return (check_success(*buff, 1));
	}
	if ((size_t)read_b < buff_size)
	{
		resize_buff(buff, len + buff_size, len + read_b);
		return (check_success(*buff, 1));
	}
	return (0);
}
