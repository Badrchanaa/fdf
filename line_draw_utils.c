/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_draw_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchanaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 16:47:45 by bchanaa           #+#    #+#             */
/*   Updated: 2024/01/15 21:31:51 by bchanaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static inline void	draw_vertical_line(t_data *data, t_point *p1, t_point *p2)
{
	int	i;
	int	dist;
	int	p_color;

	dist = p1->y - p2->y;
	i = 0;
	while (p1->y + i <= p2->y)
	{
		p_color = get_gradient_color(p1->color, p2->color, i / (double)dist);
		color_image_point(data, p1->x, p1->y + i, p_color);
		i++;
	}
}

static inline void	draw_horizontal_line(t_data *data, t_point *p1, t_point *p2)
{
	int	i;
	int	dist;
	int	p_color;

	dist = p1->x - p2->x;
	i = 0;
	while (p1->x + i <= p2->x)
	{
		
		p_color = get_gradient_color(p1->color, p2->color, i / (double)dist);
		color_image_point(data, p1->x + i, p1->y, p_color);
		i++;
	}
}

static inline void	bdraw_line_high(t_data *data, t_point *p1, t_point *p2)
{
	int		x;
	int		y;
	int		color;

	x = p1->x;
	y = p1->y;
	data->line_vars.error = 2 * data->line_vars.dx - data->line_vars.dy;
	if (p2->x < p1->x)
		data->line_vars.sx = -1;
	else
		data->line_vars.sx = 1;
	while (y != p2->y)
	{
		color = get_gradient_color(p1->color, p2->color, (double)y / data->line_vars.dy);
		color_image_point(data, x, y, color);
		if (data->line_vars.error > 0)
		{
			data->line_vars.error += 2 * (data->line_vars.dx - data->line_vars.dy);
			x += data->line_vars.sx;
		}
		else
			data->line_vars.error += 2 * data->line_vars.dx;
		y++;
	}	
}

static inline void	bdraw_line_low(t_data *data, t_point *p1, t_point *p2)
{
	int		x;
	int		y;
	double	color;

	x = p1->x;
	y = p1->y;
	data->line_vars.error = 2 * data->line_vars.dy - data->line_vars.dx;	
	if (p2->y < p1->y)
		data->line_vars.sy = -1;
	else
		data->line_vars.sy = 1;
	while (x != p2->x)
	{
		color = get_gradient_color(p1->color, p2->color, (double)x / data->line_vars.dx);
		color_image_point(data, x, y, color);
		if (data->line_vars.error > 0)
		{
			data->line_vars.error += 2 * (data->line_vars.dy - data->line_vars.dx);
			y += data->line_vars.sy;
		}
		else
			data->line_vars.error += 2 * data->line_vars.dy;
		x++;
	}
}

static inline void	draw_line_helper(t_data *data, t_point *p1, t_point *p2)
{
	data->line_vars.dx = abs(p2->x - p1->x);
	data->line_vars.dy = abs(p2->y - p1->y);
	if (p1->x > p2->x)
		data->line_vars.sx = -1;
	else
		data->line_vars.sx = 1;
	if (data->line_vars.dy < data->line_vars.dx)
	{
		if (p1->x > p2->x)
			bdraw_line_low(data, p2, p1);
		else
			bdraw_line_low(data, p1, p2);
	}
	else
	{
		if (p1->y > p2->y)
			bdraw_line_high(data, p2, p1);
		else	
			bdraw_line_high(data, p1, p2);
	}
}

void	draw_line2(t_data *data, t_point *p1, t_point *p2)
{
	if (p1->x == p2->x && p1->y == p2->y)
		color_image_point(data, p1->x, p1->y, p1->color);
	else if (p1->y == p2->y)
		draw_horizontal_line(data, p1, p2);
	else if (p1->x == p2->x)
		draw_vertical_line(data, p1, p2);
	else
		draw_line_helper(data, p1, p2);
}