/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchanaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 20:51:03 by bchanaa           #+#    #+#             */
/*   Updated: 2024/01/14 23:52:19 by bchanaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	color_image_point(t_data *data, int x, int y, unsigned int color)
{
	char	*pixel;
	int		pos;

	if (x < INFO_W || y < 0 || x > WIN_W - 1 || y > WIN_H - 1)
		return ;
	pos = y * data->size_line + x * (data->bits_per_pixel / 8);
	pixel = data->img_addr + pos;
	*(unsigned int *)pixel = color;
}

void	draw_line(t_data *data, t_point *p1, t_point *p2)
{
	int		i;
	int		dx;
	int		dy;
	double	c_percent;
	int		p_color;
	double	dist;

	i = 0;
	
	dx = p2->x - p1->x;
	dy = p2->y - p1->y;
	dist = sqrt(pow(dx, 2) + pow(dy, 2));
	//printf("%p %p dist: %f\n", p1, p2, dist);
	//ft_printf("p1->x: %10d p1->y: %10d | p2->x: %10d p2->y: %10d\n", p1->x, p1->y, p2->x, p2->y);
	//printf("		dx: %13d dy: %14d | distance: %13f\n\n", dx, dy, distance);
	while (i < (int)dist)
	{
		c_percent = (double)i / (double)dist;
		p_color = get_gradient_color(p1->color, p2->color, c_percent);
		color_image_point(data, p1->x + dx / dist * i,
						p1->y + (dy / dist * i), p_color);
		i++;
	}
}

void	clear_image(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < WIN_W)
	{	
		j = 0;
		while (j < WIN_H)
		{
			if (i < INFO_W)
				color_image_point(data, i, j, INFO_BGCOLOR);
			else
				color_image_point(data, i, j, DEFAULT_BGCOLOR);
			j++;
		}
		i++;
	}
}

void	draw_number(t_data *data, int pos, int num, char *prefix)
{
	char	*str;
	char	*tmp;

	tmp = ft_itoa(num);
	if (!tmp)
		return ;
	str = ft_strjoin(prefix, tmp);
	free(tmp);
	if (!str)
		return;
	mlx_string_put(data->mlx, data->win, (pos << 16) >> 16, (pos >> 16), C_WHITE, str);
	free(str);
}

void	draw_info(t_data *data)
{
	int	y;

	y = INFO_Y;
	draw_number(data, (y << 16) | INFO_X, data->map_width, "MAP WIDTH: ");
	y += INFO_Y_INC;
	draw_number(data, (y << 16) | INFO_X, data->map_height, "MAP HEIGHT: ");
	y += INFO_Y_INC;
	draw_number(data, (y << 16) | INFO_X, data->map_width, "MAP WIDTH: ");
	y += INFO_Y_INC;
	draw_number(data, (y << 16) | INFO_X, data->map_width, "MAP WIDTH: ");
	y += INFO_Y_INC;
}

void	link_points(t_data *data, t_point *pt, t_point *next_pt)
{
	ft_memcpy(data->draw_p1, pt, sizeof(t_point));
	ft_memcpy(data->draw_p2, next_pt, sizeof(t_point));
	transform_point(data, data->draw_p1);
	transform_point(data, data->draw_p2);
	draw_line(data, data->draw_p1, data->draw_p2);
}

int	render(t_data *data)
{
	int		i;
	t_point	**map;

	i = 0;
	ft_printf("RENDER: w=%d h=%d\n", data->map_width, data->map_height);
	clear_image(data);
	map = data->map;
	while (map[i])
	{
		if (map[i]->x < data->map_width - 1)
			link_points(data, map[i], map[i + 1]);
		if (map[i]->y < data->map_height - 1)
			link_points(data, map[i], map[((map[i]->y + 1) * data->map_width) + map[i]->x]);
		i++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}

// draw vertical line, assuming x1 == x2
// void	draw_vertical_line(t_data *data, t_point *p1, t_point *p2)
// {
// 	int	i;
// 	int	dist;
// 	int	p_color;

// 	dist = p1->y - p2->y;
// 	i = 0;
// 	while (p1->y + i <= p2->y)
// 	{
// 		p_color = get_gradient_color(p1->color, p2->color, i / (double)dist);
// 		color_image_point(data, p1->x, p1->y + i, p_color);
// 		i++;
// 	}
// }

// // draw horizontal line, assuming y1 == y2
// void	draw_horizontal_line(t_data *data, t_point *p1, t_point *p2)
// {
// 	int	i;
// 	int	dist;
// 	int	p_color;

// 	dist = p1->x - p2->x;
// 	i = 0;
// 	while (p1->x + i <= p2->x)
// 	{
		
// 		p_color = get_gradient_color(p1->color, p2->color, i / (double)dist);
// 		color_image_point(data, p1->x + i, p1->y, p_color);
// 		i++;
// 	}
	
// }

// void	bline(t_data *data, t_point *p1, t_point *p2)
// {
	
// }

// void	draw_line(t_data *data, t_point *p1, t_point *p2)
// {
// 	int				dx;
// 	int				dy;
// 	unsigned int	coords;

// 	coords = p1->x;
// 	coords |= p1->y << 16;
// 	if (p1->x == p2->x)
// 		draw_vertical_line(data, p1, p2);
// 	else if (p1->y == p2->y)
// 		draw_horizontal_line(data, p1, p2);
// 	bline(data, p1, p2);
// }