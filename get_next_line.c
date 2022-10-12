/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:56:30 by lorobert          #+#    #+#             */
/*   Updated: 2022/10/12 11:37:54 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

void	free_mem(void *p)
{
	if (p)
		free(p);
}

int	find_newline(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		return (i);
	return (-1);
}

char	*read_until_line(int fd, char **buffer, char *raw_line)
{
	int		len;

	*buffer = malloc(sizeof(char) * BUFFER_SIZE);
	if (!*buffer)
		return (NULL);
	len = 1;
	while (len)
	{
		len = read(fd, *buffer, BUFFER_SIZE);
		if (len == -1)
			return (NULL);
		if (!len)
			return (raw_line);
		if (!raw_line)
			raw_line = ft_strdup(*buffer);
		else
			raw_line = ft_strjoin(raw_line, *buffer);
		if (find_newline(raw_line) != -1)
			return (raw_line);
	}
	return (raw_line);
}

char	*clean_line(char *raw_line, char **remainder)
{
	int		index;
	char	*clean_line;

	index = find_newline(raw_line);
	if (index == -1)
		return (raw_line);
	clean_line = ft_substr(raw_line, 0, index + 1);
	*remainder = ft_substr(raw_line, index + 1, ft_strlen(raw_line) - index);
	free_mem(raw_line);
	return (clean_line);
}

char	*get_next_line(int fd)
{
	static char	*remainder = NULL;
	char		*line;
	char		*buffer;

	if (fd < 0 || !BUFFER_SIZE)
		return (NULL);
	line = read_until_line(fd, &buffer, remainder);
	free_mem(buffer);
	if (!line)
	{
		free_mem(remainder);
		return (NULL);
	}
	line = clean_line(line, &remainder);
	if (!line)
	{
		free_mem(remainder);
		return (NULL);
	}
	return (line);
}
