/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: default <default@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 13:06:14 by damateos          #+#    #+#             */
/*   Updated: 2024/02/05 22:48:36 by default          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

/* Resizes the buffer to the new_size or initializes it if NULL.
 * New size is the length of the string
 * Null-terminates the buffer string */
void	resize_line(char **line, size_t new_size)
{
	char	*temp;
	size_t	i;

	temp = malloc(new_size + 1);
	if (!temp && *line)
	{
		free(*line);
		*line = NULL;
	}
	i = 0;
	while (*line && (*line)[i] && i < new_size)
	{
		temp[i] = (*line)[i];
		i++;
	}
	temp[new_size] = '\0';
	if (*line)
		free(*line);
	*line = temp;
}

int	get_newline_i(const char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

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
