/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 20:05:00 by damateos          #+#    #+#             */
/*   Updated: 2024/02/04 15:26:25 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* The 42 macs memory page size is 4KiB.
 * This optimizes memory usage and caching by the system.
 * We can see the system page size executing `sysctl vm.pagesize` */

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 4094
#endif

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static size_t	len;
	int				status;
	char			*buff;

	buff = NULL;
	status = 0;
	len = 0;
	while (status != 1)
	{
		status = read_chunk(buff, &len, BUFFER_SIZE, fd);
		if (status == -1)
			return (NULL);
	}
	return (buff);
}
