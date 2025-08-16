/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helde-so <helde-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 13:51:42 by helde-so          #+#    #+#             */
/*   Updated: 2025/08/15 21:46:49 by helde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*fill_line(int fd, char *buf, char *line)
{
	int		bytes_read;
	char	*tmp;

	bytes_read = 1;
	tmp = NULL;
	while (bytes_read != 0)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read == -1)
			return (NULL);
		if (bytes_read == 0)
			break ;
		buf[bytes_read] = '\0';
		if (!line)
			line = ft_strdup("");
		tmp = line;
		line = ft_strjoin(tmp, buf);
		free(tmp);
		tmp = NULL;
		if (ft_strchr(line, '\n'))
			break ;
	}
	return (line);
}

static char	*separate(char *line)
{
	int		end;
	char	*rest;
	char	*result_line;

	if (line && ft_strchr(line, '\n'))
	{
		result_line = ft_strchr(line, '\n');
		end = ft_strlen(line) - ft_strlen(result_line) + 1;
		rest = ft_strdup(result_line + 1);
		line[end] = '\0';
		return (rest);
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*line[1024];
	char		*buffer;
	char		*result;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	result = fill_line(fd, buffer, line[fd]);
	free(buffer);
	buffer = NULL;
	if (result == NULL && line[fd])
		free(line[fd]);
	line[fd] = separate(result);
	if (result == NULL || *result == '\0')
	{
		free(result);
		result = NULL;
	}
	return (result);
}
