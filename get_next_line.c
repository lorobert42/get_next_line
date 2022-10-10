/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:56:30 by lorobert          #+#    #+#             */
/*   Updated: 2022/10/10 16:11:41 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_until_line(int fd)
{
	char	*buffer;
	char	*raw_line;
	int		len;

	buffer = malloc(sizeof(char) * BUFFER_SIZE);
	if (!buffer)
		return (NULL);
	raw_line = NULL;
	len = 1;
	while (len)
	{
		len = read(fd, buffer, BUFFER_SIZE);
		if (!raw_line)
			raw_line = ft_strdup(buffer);
		else
			raw_line = ft_strjoin(raw_line, buffer);
		if (find_newline(raw_line))
			return (raw_line);
	}
	return (raw_line);
}

char	*get_next_line(int fd)
{
	if (fd < 0 || !BUFFER_SIZE)
		return (NULL);
}
