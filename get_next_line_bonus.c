/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkakuna <vkakuna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 17:37:25 by vkakuna           #+#    #+#             */
/*   Updated: 2021/12/09 16:09:59 by vkakuna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include "get_next_line.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
#endif

int	line_length(char *buf)
{
	int	i;

	i = 0;
	while (buf[i] != '\n' && buf[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*get_line(char *remainder)
{
	char	*line;
	int		i;

	i = 0;
	if (!remainder[i])
		return (NULL);
	line = (char *)malloc(sizeof(char) * (line_length(remainder) + 2));
	if (!line)
		return (NULL);
	while (remainder[i] != '\n' && remainder[i] != '\0')
	{
		line[i] = remainder[i];
		i++;
	}
	if (remainder[i] == '\n')
	{
		line[i] = remainder[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_read(int fd, char *remainder)
{
	char	*buf;
	int		byte_read;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	byte_read = 1;
	while (byte_read != 0 && !ft_strchr(remainder, '\n'))
	{
		byte_read = read(fd, buf, BUFFER_SIZE);
		if (byte_read == -1)
		{
			free (buf);
			return (NULL);
		}
		buf[byte_read] = '\0';
		remainder = ft_strjoin(remainder, buf);
	}
	free (buf);
	return (remainder);
}

char	*get_remainder(char *remainder)
{
	int		i;
	char	*real_remainder;
	int		j;

	i = 0;
	i = line_length(remainder);
	if (!remainder[i])
	{
		free(remainder);
		return (NULL);
	}
	real_remainder = (char *)malloc(sizeof(char)
			* (ft_strlen(remainder) - i + 1));
	if (!real_remainder)
		return (NULL);
	i++;
	j = 0;
	while (remainder[i])
		real_remainder[j++] = remainder[i++];
	real_remainder[j] = '\0';
	free (remainder);
	return (real_remainder);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*remainder[OPEN_MAX];

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > OPEN_MAX)
		return (NULL);
	remainder[fd] = ft_read(fd, remainder[fd]);
	if (!remainder[fd])
		return (NULL);
	line = get_line(remainder[fd]);
	remainder[fd] = get_remainder(remainder[fd]);
	return (line);
}
