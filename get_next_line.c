/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 20:05:00 by damateos          #+#    #+#             */
/*   Updated: 2024/02/04 20:06:39 by damateos         ###   ########.fr       */
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
		ft_memcpy(dst, src, src_len + 1);
	else if (dstsize != 0)
	{
		ft_memcpy(dst, src, dstsize - 1);
		dst[dstsize - 1] = '\0';
	}
	return (src_len);
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
	size_t		prev_len;
	size_t		len;
	int			status;
	static char	*buff;

	status = 0;
	prev_len = ft_strlen(buff);
	len = prev_len;
	while (status < 1)
	{
		status = read_chunk(&buff, len, BUFFER_SIZE, fd);
		if (status == -1)
			return (NULL);
		len = ft_strlen(buff);
	}
	if (ft_strlen(buff) == prev_len)
		return (NULL);
	return (ft_substr(buff, prev_len, len - prev_len));
}
// Fix: once we have read some bytes, we can not re-read them,
// so we have to always keep them.
/*
 * buffer
 * chunk
 * if read chunk:
 * 	buffer += chunk
 * 	if '\n' in buffer
 * 	  get
 */
