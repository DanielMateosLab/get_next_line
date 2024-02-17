/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 15:30:42 by damateos          #+#    #+#             */
/*   Updated: 2024/02/04 15:54:58 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	char	*line;
	int		fd;
	int		started;

	(void) argc;
	started = 0;
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (1);
	line = "START READING:\n";
	while (line)
	{
		printf("%s", line);
		if (started && line)
			free(line);
		line = get_next_line(fd);
		started = 1;
	}
	return (0);
}
