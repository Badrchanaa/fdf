/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchanaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 23:03:46 by bchanaa           #+#    #+#             */
/*   Updated: 2024/01/24 15:10:25 by bchanaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <unistd.h>
#include <fcntl.h>

static int	populate_matrix(t_list *lst, t_point **matrix, t_data *data)
{
	int		x;
	int		y;
	char	**arr;

	x = 0;
	y = 0;
	while (lst)
	{
		arr = ft_split(lst->content, ' ');
		if (!arr)
			return (1);
		x = -1;
		while (arr[++x])
		{
			matrix[(data->map_width * y) + x] = parse_point(arr[x], x, y, data);
			if (!matrix[(data->map_width * y) + x])
				return (free_2darray((void **)arr, true), 1);
		}
		if (fill_matrix_line(matrix, x, y, data) != 0)
			return (free_2darray((void **)arr, true), 1);
		free_2darray((void **)arr, true);
		lst = lst->next;
		y++;
	}
	return (0);
}

t_point	**get_map_matrix(t_list *lst, t_data *data)
{
	t_point	**matrix;

	if (!lst)
		return (NULL);
	data->map_width = get_map_width(lst, data->map_height);
	if (data->map_width == -1)
		return (NULL);
	matrix = ft_calloc(sizeof(t_point *), \
						(data->map_height * (data->map_width)) + 1);
	if (!matrix)
		return (NULL);
	if (populate_matrix(lst, matrix, data))
		return (free_2darray((void **)matrix, true), (NULL));
	return (matrix);
}

t_point	**parse_landscape(char *filename, t_data *data)
{
	int		fd;
	char	*line;
	t_list	*lst;

	data->map_height = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("fdf");
		exit(EXIT_FAILURE);
	}
	line = get_next_line(fd);
	lst = NULL;
	while (line)
	{
		if (!data->has_color && ft_strnstr(line, ",0x", ft_strlen(line)))
			data->has_color = 1;
		ft_lstadd_back(&lst, ft_lstnew(line));
		(data->map_height)++;
		line = get_next_line(fd);
	}
	data->map = get_map_matrix(lst, data);
	ft_lstclear(&lst, free);
	return (data->map);
}
