/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moduwole <moduwole@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 00:27:20 by moduwole          #+#    #+#             */
/*   Updated: 2022/11/12 00:27:20 by moduwole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*dst2;
	char	*src2;
	size_t	i;

	if (n == 0 || dst == src)
		return (dst);
	if (!dst || !src)
		return (NULL);
	i = 0;
	dst2 = (char *)dst;
	src2 = (char *)src;
	while (i < n)
	{
		dst2[i] = src2[i];
		i++;
	}
	return ((void *)dst);
}

int	find_line(char **ret_line, char buff_store[], int *rd_bytes)
{
	char	*linepos;
	int		i;

	i = -1;
	linepos = ft_strchr(buff_store, '\n');
	if (linepos)
	{
		*ret_line = ft_calloc(sizeof(char), (linepos - buff_store) + 2);
		ft_memcpy(*ret_line, buff_store, linepos - buff_store + 1);
		while (linepos[++i + 1] != '\0')
			buff_store[i] = linepos[i + 1];
		ft_bzero(&buff_store[i], MAX_LINE - i);
		return (1);
	}
	if (*rd_bytes == 0)
	{
		*ret_line = ft_calloc(sizeof(char), MAX_LINE + 1);
		ft_memcpy(*ret_line, buff_store, MAX_LINE);
		*rd_bytes = -1;
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static char	buff_store[MAX_FD][MAX_LINE];
	char		*temp_storage;
	char		*ret_line;
	int			rd_bytes;

	if (fd < 0 || fd > MAX_FD || BUFFER_SIZE <= 0 || BUFFER_SIZE > MAX_LINE)
		return (NULL);
	temp_storage = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	rd_bytes = read(fd, temp_storage, BUFFER_SIZE);
	ft_strcat(buff_store[fd], temp_storage);
	free(temp_storage);
	if (rd_bytes < 0 || (rd_bytes <= 0 && buff_store[fd][0] == '\0'))
	{
		ft_bzero(buff_store[fd], MAX_LINE);
		return (NULL);
	}
	if (find_line (&ret_line, buff_store[fd], &rd_bytes) == 1)
		return (ret_line);
	if (rd_bytes == -1)
	{
		ft_bzero(buff_store[fd], MAX_LINE);
		return (ret_line);
	}
	return (get_next_line(fd));
}
