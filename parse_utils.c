/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchanaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 18:54:51 by bchanaa           #+#    #+#             */
/*   Updated: 2024/01/13 23:42:28 by bchanaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	_parse_point_color(t_point *point, char *s)
{
	char	**arr;

	arr = ft_split(s, ',');
	if (!arr)
		return (1);
	if (!*arr || !*(arr + 1))
		return (1);
	point->z = ft_atoi(arr[0]);
	point->color = get_color_from_hex(arr[1]);
	free_2darray((void **)arr, true);
	return (0);
}

t_point	*_parse_point(char *s, int x, int y, t_data *data)
{
	t_point	*point;

	if (!s)
		return (NULL);
	point = malloc(sizeof(t_point));
	if (!point)
		return (NULL);
	
	if (ft_strchr(s, ','))
	{
		if (_parse_point_color(point, s) != 0)
			return free(point), (NULL);
	}
	else
	{
		point->color = C_WHITE;
		point->z = ft_atoi(s);
	}
	point->x = x;
	point->y = y;
	if (data->min_z > point->z)
		data->min_z = point->z;
	if (data->max_z < point->z)
		data->max_z = point->z;
	return (point);
}

static int	get_map_width(t_list *lst, int height)
{
	t_list	*curr;

	int		width;
	int		height_c;
	int		tmp;
	width = count_split(lst->content, ' ');
	height_c = 1;
	if (!width)
		return (-1);
	curr = lst->next;
	while (curr)
	{
		tmp = count_split(curr->content, ' ');
		if (tmp > width)
			width = tmp;
		curr = curr->next;
		height_c++;
	}
	if (height_c != height)
		return (-1);
	return (width);
}

int	fill_matrix_line(t_point **matrix, int x, int y, t_data *data)
{
	int		i;
	t_point	*pt;

	i = x;
	while (i < data->map_width)
	{
		
		pt = malloc(sizeof(t_point));
		if (!pt)
			return (1);
		pt->x = i;
		pt->y = y;
		pt->z = INT_MIN;
		pt->color = C_WHITE;
		matrix[(data->map_width * y) + i] = pt;
		i++;
	}
	return (0);
}

void	set_filled_z(t_point **map, t_data *data)
{
	int	i;
	int	medium_z;

	medium_z = (data->max_z + data->min_z) / 2;
	i = 0;
	while (map[i])
	{
		if (map[i]->z < data->min_z)
			map[i]->z = medium_z;
		i++;
	}
}

static int	_populate_matrix(t_list *lst, t_point **matrix, t_data *data)
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
			matrix[(data->map_width * y) + x] = _parse_point(arr[x], x, y, data);
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
	matrix = ft_calloc(sizeof(t_point *), (data->map_height * (data->map_width)) + 1);
	if (!matrix)
		return (NULL);
	if (_populate_matrix(lst, matrix, data))
		return free_2darray((void **)matrix, true), (NULL);
	set_filled_z(matrix, data);
	return (matrix);
}
