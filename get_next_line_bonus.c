/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:56:30 by lorobert          #+#    #+#             */
/*   Updated: 2022/10/13 10:42:49 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

void	free_mem(char **p)
{
	if (p && *p)
	{
		free(*p);
		*p = NULL;
	}
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

void	read_until_line(int fd, char **remainder, char **tmp)
{
	int		len;
	char	*buffer;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return ;
	len = 1;
	while (len)
	{
		len = read(fd, buffer, BUFFER_SIZE);
		if (len <= 0)
			break ;
		buffer[len] = '\0';
		if (!*remainder)
			*remainder = ft_strdup(buffer);
		else
		{
			*tmp = ft_strjoin(*remainder, buffer);
			free_mem(remainder);
			*remainder = *tmp;
		}
		if (find_newline(buffer) != -1)
			break ;
	}
	free_mem(&buffer);
}

char	*clean_line(char **rest, char **tmp)
{
	int		index;
	char	*clean_line;

	index = find_newline(*rest);
	if (index == -1)
	{
		clean_line = ft_strdup(*rest);
		free_mem(rest);
		return (clean_line);
	}
	clean_line = ft_substr(*rest, 0, index + 1);
	*tmp = ft_substr(*rest, index + 1, ft_strlen(*rest) - index);
	free_mem(rest);
	*rest = *tmp;
	return (clean_line);
}

char	*get_next_line(int fd)
{
	static char	*remainder[4096];
	char		*line;
	char		*tmp;

	if (fd < 0 || !BUFFER_SIZE)
		return (NULL);
	read_until_line(fd, &remainder[fd], &tmp);
	if (!remainder[fd] || !remainder[fd][0])
	{
		free_mem(&remainder[fd]);
		return (NULL);
	}
	line = clean_line(&remainder[fd], &tmp);
	if (!line)
	{
		free_mem(&remainder[fd]);
		return (NULL);
	}
	return (line);
}
