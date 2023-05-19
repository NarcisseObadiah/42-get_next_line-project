/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobadiah <mobadiah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 12:40:10 by mobadiah          #+#    #+#             */
/*   Updated: 2023/05/12 18:42:04 by mobadiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_read_file(int fd, char *stash)
{
	int		read_size;
	char	*buffer;

	buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (free(buffer), NULL);
	read_size = read(fd, buffer, BUFFER_SIZE);
	if (read_size == -1)
		return (free(buffer), free(stash), NULL);
	while (read_size > 0)
	{
		stash = ft_strjoin(stash, buffer, read_size);
		if (stash && ft_strchr(stash, '\n'))
			break ;
		read_size = read(fd, buffer, BUFFER_SIZE);
		if (read_size == -1)
			return (free(buffer), buffer = NULL, free(stash), NULL);
		if (read_size == 0)
			return (free(buffer), buffer = NULL, stash);
	}
	free(buffer);
	buffer = NULL;
	return (stash);
}

static char	*ft_extract_line(char *stash)
{
	char	*line;
	int		len;

	if (!stash)
		return (NULL);
	len = 0;
	while (stash[len] != '\0' && stash[len] != '\n')
		len++;
	if (stash[len] != '\n')
	{
		line = (char *) malloc(sizeof(char) * (len + 1));
		if (!line)
			return (NULL);
		ft_strlcpy(line, stash, len + 1);
	}
	else
	{
		line = (char *) malloc(sizeof(char) * (len + 2));
		if (!line)
			return (NULL);
		ft_strlcpy(line, stash, len + 2);
	}
	return (line);
}

static char	*ft_adjust_stash(char *stash, int line_len)
{
	char	*new_stash;
	int		r_len;

	new_stash = (char *)malloc((ft_strlen(stash) - line_len + 1));
	if (!new_stash)
		return (free(stash), free(new_stash), NULL);
	r_len = 0;
	while (stash[line_len + r_len])
	{
		new_stash[r_len] = stash[line_len + r_len];
		r_len++;
	}
	new_stash[r_len] = '\0';
	if (new_stash[0] == 0)
		return (free(stash), free(new_stash), NULL);
	return (free(stash), new_stash);
}

char	*get_next_line(int fd)
{
	static char	*stash[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash[fd] = ft_read_file(fd, stash[fd]);
	if (!stash[fd])
		return (NULL);
	line = ft_extract_line(stash[fd]);
	stash[fd] = ft_adjust_stash(stash[fd], ft_strlen(line));
	return (line);
}
