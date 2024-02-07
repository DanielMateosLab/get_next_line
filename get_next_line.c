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

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 4094
#endif

#include "get_next_line.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*dst_u;
	unsigned char	*src_u;

	if (!dst && !src)
		return (dst);
	dst_u = (unsigned char *)dst;
	src_u = (unsigned char *)src;
	while (n-- > 0)
		dst_u[n] = src_u[n];
	return (dst);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dst_u;
	unsigned char	*src_u;
	size_t			i;

	if ((!dst && !src) || !len || dst == src)
		return (dst);
	if (dst > src)
		return (ft_memcpy(dst, src, len));
	dst_u = (unsigned char *)dst;
	src_u = (unsigned char *)src;
	i = 0;
	while (i < len)
	{
		dst_u[i] = src_u[i];
		i++;
	}
	return (dst);
}

size_t	ft_strlen(char const *s)
{
	size_t	size;

	size = 0;
	while (s && s[size])
		size++;
	return (size);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	src_len;

	src_len = ft_strlen(src);
	if (dstsize >= src_len + 1)
		ft_memmove(dst, src, src_len + 1);
	else if (dstsize != 0)
	{
		ft_memmove(dst, src, dstsize - 1);
		dst[dstsize - 1] = '\0';
	}
	return (src_len);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	src_len;
	size_t	dst_len;

	src_len = ft_strlen(src);
	dst_len = 0;
	while (dst[dst_len] && dst_len < dstsize)
		dst_len++;
	if (dst_len >= dstsize)
		return (dstsize + src_len);
	if (dstsize > dst_len + src_len)
		ft_memcpy(dst + dst_len, src, src_len + 1);
	else
	{
		ft_memcpy(dst + dst_len, src, dstsize - dst_len - 1);
		dst[dstsize - 1] = '\0';
	}
	return (src_len + dst_len);
}

// dest_len does not include the '\0'
char	*ft_substr(char const *s, unsigned int start, size_t dest_len)
{
	char	*sub;
	size_t	source_len;

	if (s == NULL)
		return (NULL);
	source_len = ft_strlen(s);
	if (start > source_len)
		dest_len = 0;
	else if (dest_len > source_len - start)
		dest_len = source_len - start;
	sub = malloc((dest_len + 1) * sizeof(char));
	if (sub == NULL)
		return (NULL);
	if (start > source_len)
		sub[0] = '\0';
	else
		ft_strlcpy(sub, s + start, dest_len + 1);
	return (sub);
}

char	*get_next_line(int fd)
{
	static char	buff[BUFFER_SIZE + 1] = {'\0'};
	char		*line;
	ssize_t		bytes_read;
	int			newline_i;
	int		curr_len;

	if (BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	while (1)
	{
		curr_len = ft_strlen(line);
		if (!buff[0])
		{
			bytes_read = read(fd, buff, BUFFER_SIZE);
			if (bytes_read == -1)
			{
				if (line)
					free(line);
				return (NULL);
			}
			if (!bytes_read)
			{
				if (!curr_len)
					return (NULL);
				return (line);
			}
			buff[bytes_read] = '\0';
		}
		newline_i = get_newline_i(buff);
		if (newline_i != -1)
		{
			resize_buff(&line, curr_len + newline_i + 1);
			if (!line)
				return (NULL);
			ft_strlcpy(line + curr_len, buff, newline_i + 2);
			ft_strlcpy(buff, buff + newline_i + 1, bytes_read - newline_i + 1);
			return (line);
		}
		resize_buff(&line, curr_len + bytes_read);
		if (!line)
			return (NULL);
		ft_strlcpy(line + curr_len, buff, bytes_read + 1);
		buff[0] = '\0';
		/*
		   Remember berni's approach. You may use strjoin and just put a \0 after the newline found
		   High level: read chunks until finding a new line.
		   Store remaining chunk in buffer.
		*/
	}
}
