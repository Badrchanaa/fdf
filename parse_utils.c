/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchanaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 18:54:51 by bchanaa           #+#    #+#             */
/*   Updated: 2023/12/23 17:27:37 by bchanaa          ###   ########.fr       */
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

t_point	*_parse_point(char *s, int x, int y)
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
	return (point);
}

static int	validate_land_width(t_list *lst, int height)
{
	t_list	*curr;

	int		width;
	int		height_c;
	
	width = count_split(lst->content, ' ');
	height_c = 1;
	if (!width)
		return (-1);
	curr = lst->next;
	while (curr)
	{
		if (count_split(curr->content, ' ') != width)
			return (-1);
		curr = curr->next;
		height_c++;
	}
	if (height_c != height)
		return (-1);
	return (width);
}

static int	_populate_matrix(t_list *lst, t_point **matrix, int width)
{
	int		x;
	int		y;
	char	**arr;
	t_point	*pt;

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
			pt = _parse_point(arr[x], x, y);
			if (!pt)
				return (free_2darray((void **)arr, true), 1);
			matrix[(width * y) + x] = pt;
		}
		free_2darray((void **)arr, true);
		lst = lst->next;
		y++;
	}
	return (0);
}

t_point	**get_land_matrix(t_list *lst, int height, int *width)
{
	t_point	**matrix;

	if (!lst)
		return (NULL);
	*width = validate_land_width(lst, height);
	if (*width == -1)
		return (NULL);
	matrix = ft_calloc(sizeof(t_point *), (height * (*width)) + 1);
	if (!matrix)
		return (NULL);
	if (_populate_matrix(lst, matrix, *width))
		return free_2darray((void **)matrix, true), (NULL);
	return (matrix);
}
