/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchanaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:47:42 by bchanaa           #+#    #+#             */
/*   Updated: 2023/12/15 17:09:53 by bchanaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

static char	*ft_realloc(char *s, size_t size, char *buff, size_t buff_size)
{
	char	*new_s;

	if (size + 1 > SIZE_MAX - buff_size)
	{
		free(s);
		return (NULL);
	}
	new_s = malloc(sizeof(char) * (size + buff_size + 1));
	if (!new_s)
	{
		free(s);
		return (NULL);
	}
	if (s && size > 0)
		ft_memmove(new_s, s, size);
	if (buff && buff_size)
		ft_memmove(new_s + size, buff, buff_size);
	free(s);
	new_s[size + buff_size] = '\0';
	return (new_s);
}

static char	*ft_get_line(char *buff, char **cache_buff)
{
	size_t	i;
	char	*line;

	i = 0;
	while (buff[i] && buff[i] != '\n')
		i++;
	if (buff[i] == '\n')
		i++;
	if (!buff[i])
		return (ft_substr(buff, 0, i + 1));
	line = ft_substr(buff, 0, i);
	if (!line)
		return (NULL);
	*cache_buff = ft_substr(buff, i, ft_strlen(buff + i));
	if (!*cache_buff)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

static int	read_next_line(int fd, char **line, size_t line_size)
{
	char	*buff;
	ssize_t	r_bytes;

	buff = malloc(sizeof(char) * BUFFER_SIZE);
	if (!buff)
		return (1);
	r_bytes = read(fd, buff, BUFFER_SIZE);
	while (r_bytes > 0)
	{
		*line = ft_realloc(*line, line_size, buff, r_bytes);
		if (!*line)
		{
			free(buff);
			return (1);
		}
		line_size += r_bytes;
		if (ft_strnchr(buff, '\n', r_bytes))
			break ;
		r_bytes = read(fd, buff, BUFFER_SIZE);
	}
	free(buff);
	if (r_bytes < 0)
		return (1);
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*cache_buff;
	char		*line;
	char		*buff;
	size_t		line_size;
	int			is_err;

	if (fd < 0 || !BUFFER_SIZE_OK)
		return (NULL);
	buff = cache_buff;
	cache_buff = NULL;
	line_size = 0;
	is_err = 0;
	if (buff)
		line_size = ft_strlen(buff);
	if (!buff || !ft_strnchr(buff, '\n', line_size))
		is_err = read_next_line(fd, &buff, line_size);
	if (!buff || is_err)
	{
		free(buff);
		return (NULL);
	}
	line = ft_get_line(buff, &cache_buff);
	free(buff);
	return (line);
}
