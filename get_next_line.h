/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: default <default@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 12:03:11 by damateos          #+#    #+#             */
/*   Updated: 2024/02/05 22:48:47 by default          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

char	*get_next_line(int fd);
void	*ft_memcpy(void *dst, const void *src, size_t n);
int		get_newline_i(const char *s);
void	resize_line(char **buff, size_t new_size);
size_t	ft_strlen(char const *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
void	read_until_nl_eof(char **line, int fd);

#endif
