/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchanaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 20:51:03 by bchanaa           #+#    #+#             */
/*   Updated: 2024/01/12 22:51:46 by bchanaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	color_image_point(t_data *data, int x, int y, unsigned int color)
{
	char	*pixel;
	int		pos;

	if (x < 0 || y < 0 || x > WIN_W - 1 || y > WIN_H - 1)
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
			color_image_point(data, i, j, 0);
			j++;
		}
		i++;
	}
}

int draw_land(t_data *data)
{
	int		i;
	t_point	**map;
	t_point	*curr_pt;
	t_point	*next_pt;
	int		x;
	int		y;

	i = 0;
	ft_printf("drawing land w: %d h: %d\n", data->map_width, data->map_height);
	clear_image(data);
	map = data->map;
	while (map[i])
	{
		curr_pt = rotate_point(data, map[i]);
		next_pt = NULL;
		x = i % data->map_width;
		y = i / data->map_width;
		//printf("x: %d y:%d\n", x , y);
		if (x < data->map_width - 1)
		{
			next_pt = rotate_point(data, map[i + 1]);
			draw_line(data, curr_pt, next_pt);
		}
		if (y < data->map_height - 1)
		{
			next_pt = rotate_point(data, map[((y + 1) * data->map_width) + x]);
			draw_line(data, curr_pt, next_pt);
		}
		free(next_pt);
		free(curr_pt);
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