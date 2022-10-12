/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 10:06:47 by lorobert          #+#    #+#             */
/*   Updated: 2022/10/12 10:58:34 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "get_next_line.h"

int	main(int argc, char **argv)
{
	int		fd;
	char	*line;

	(void) argc;
	line = "";
	fd = open(argv[1], O_RDONLY);
	while (line)
	{
		line = get_next_line(fd);
		if (!line)
			printf("Error or end of file\n");
		else
			printf("%s", line);
	}
	close(fd);
}
