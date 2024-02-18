/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: default <default@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 20:05:00 by damateos          #+#    #+#             */
/*   Updated: 2024/02/07 21:53:26 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* The 42 macs memory page size is 4KiB.
 * This optimizes memory usage and caching by the system.
 * We can see the system page size executing `sysctl vm.pagesize` */

#include "get_next_line_bonus.h"

size_t	ft_strlen(char const *s)
{
	size_t	size;

	size = 0;
	while (s && s[size])
		size++;
	return (size);
}

void	buff_to_line(char **line, char *buff)
{
	if (ft_strlen(buff) == 0)
	{
		resize_line(line, 0);
		return ;
	}
	resize_line(line, ft_strlen(buff));
	if (*line)
		ft_memcpy(*line, buff, ft_strlen(buff));
}

void	read_until_nl_eof(char **line, int fd)
{
	int		nl_index;
	int		bytes_read;
	size_t	len;

	nl_index = get_newline_i(*line);
	bytes_read = 1;
	while (nl_index == -1 && bytes_read != 0)
	{
		resize_line(line, (len = ft_strlen(*line)) + BUFFER_SIZE + 1);
		if (!*line)
			return ;
		bytes_read = read(fd, *line + len, BUFFER_SIZE);
		if (bytes_read == -1 || (!bytes_read && !len))
		{
			if (line)
			{
				free(*line);
				*line = NULL;
			}
			return ;
		}
		(*line)[len + bytes_read] = '\0';
		nl_index = get_newline_i(*line);
	}
}

char	*save_suffix_and_return_line(char *line, char *buff)
{
	int	line_end_i;

	line_end_i = get_newline_i(line);
	if (line_end_i == -1)
	{
		buff[0] = '\0';
		return (line);
	}
	ft_strlcpy(buff, line + line_end_i + 1, ft_strlen(line) - line_end_i);
	line[line_end_i + 1] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	static char	buff[4096][BUFFER_SIZE + 1];
	char		*line;

	if (BUFFER_SIZE <= 0 || fd < 0 || fd >= 4096)
		return (NULL);
	line = NULL;
	buff_to_line(&line, buff[fd]);
	if (!line)
		return (NULL);
	read_until_nl_eof(&line, fd);
	if (!line)
	{
		buff[fd][0] = '\0';
		return (NULL);
	}
	return (save_suffix_and_return_line(line, buff[fd]));
}
