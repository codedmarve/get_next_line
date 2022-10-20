/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moduwole <moduwole@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 17:22:21 by moduwole          #+#    #+#             */
/*   Updated: 2022/06/23 17:22:21 by moduwole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	bufcpy(char *buffer)
{
	char	cpy[BUFFER_SIZE + 1];
	int		i;

	cpy[BUFFER_SIZE] = 0;
	i = 0;
	while (i < BUFFER_SIZE)
		cpy[i++] = '\0';
	ft_strcpy(cpy, buffer);
	i = 0;
	while (buffer[i] != '\0' && buffer[i] != '\n')
		i++;
	if (i == BUFFER_SIZE && buffer[i] == 0)
		buffer[0] = 0;
	else
		ft_strcpy(buffer, &cpy[i + 1]);
	return ;
}

char	*put_line(char *str, int bytes)
{
	char	*line;
	int		i;

	if (!str)
		return (NULL);
	if (!bytes && !ft_strchr(str, '\n'))
		return (str);
	i = 0;
	while (str[i] != '\n')
		i++;
	line = ft_substr(str, 0, i + 1);
	free(str);
	return (line);
}

char	*join(char *str, char *buffer)
{
	char	*s;
	int		i;
	int		j;

	i = 0;
	j = 0;
	s = malloc(ft_strlen(str) + ft_strlen(buffer) + 1);
	if (s == 0)
		return (NULL);
	if (str)
	{
		while (str[i])
		{
			s[i] = str[i];
			i++;
		}
		free(str);
	}
	while (buffer[j])
		s[i++] = buffer[j++];
	s[i] = '\0';
	return (s);
}

char	*refresh(char *str, char *buffer)
{
	char	*new;

	if (!str)
		new = join(0, buffer);
	else
		new = join(str, buffer);
	return (new);
}

char	*get_next_line(int fd)
{
	static char	buffer[1024][BUFFER_SIZE + 1];
	char		*str;
	int			bytes;

	str = NULL;
	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	if (buffer[fd][0])
		str = ft_strdup(buffer[fd]);
	buffer[fd][BUFFER_SIZE] = '\0';
	while (!ft_strchr(str, '\n'))
	{
		bytes = read(fd, buffer[fd], BUFFER_SIZE);
		if (!bytes || bytes == -1)
			break ;
		if (bytes < BUFFER_SIZE)
			buffer[fd][bytes] = '\0';
		str = refresh(str, buffer[fd]);
	}
	bufcpy(buffer[fd]);
	return (put_line(str, bytes));
}
