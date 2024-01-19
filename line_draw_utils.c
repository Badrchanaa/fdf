/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_draw_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchanaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 16:47:45 by bchanaa           #+#    #+#             */
/*   Updated: 2024/01/18 22:49:51 by bchanaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_vertical_line(t_data *data, t_point *p1, t_point *p2)
{
	int		i;
	int		dist;
	int		p_color;
	t_point	*tmp;

	if (p1->y > p2->y)
	{
		tmp = p1;
		p1 = p2;
		p2 = tmp;
	}
	dist = p1->y - p2->y;
	i = 0;
	while (p1->y + i <= p2->y)
	{
		p_color = get_gradient_color(p1->color, p2->color, i / (float)dist);
		color_image_point(data, p1->x, p1->y + i, p_color);
		i++;
	}
}

void	draw_horizontal_line(t_data *data, t_point *p1, t_point *p2)
{
	int	i;
	int	dist;
	int	p_color;
	t_point	*tmp;

	if (p1->x > p2->x)
	{
		tmp = p1;
		p1 = p2;
		p2 = tmp;
	}
	dist = p1->x - p2->x;
	i = 0;
	while (p1->x + i <= p2->x)
	{
		
		p_color = get_gradient_color(p1->color, p2->color, i / (float)dist);
		color_image_point(data, p1->x + i, p1->y, p_color);
		i++;
	}
}

void	bdraw_line_high(t_data *data, t_point *p1, t_point *p2)
{
	int			x;
	int			y;
	int			color;
	t_line_vars	*v;

	v = data->line_vars;
	x = p1->x;
	y = p1->y;
	v->error = 2 * v->dx - v->dy;
	if (p2->x < p1->x)
		v->sx = -1;
	else
		v->sx = 1;
	while (y != p2->y)
	{
		color = get_gradient_color(p1->color, p2->color, (float)y / v->dy);
		color_image_point(data, x, y, color);
		if (v->error > 0)
		{
			v->error += 2 * (v->dx - v->dy);
			x += v->sx;
		}
		else
			v->error += 2 * v->dx;
		y++;
	}	
}

void	bdraw_line_low(t_data *data, t_point *p1, t_point *p2)
{
	int		x;
	int		y;
	float	color;
	t_line_vars	*v;

	v = data->line_vars;
	x = p1->x;
	y = p1->y;
	v->error = 2 * v->dy - v->dx;	
	if (p2->y < p1->y)
		v->sy = -1;
	else
		v->sy = 1;
	while (x != p2->x)
	{
		color = get_gradient_color(p1->color, p2->color, (float)x / v->dx);
		color_image_point(data, x, y, color);
		if (v->error > 0)
		{
			v->error += 2 * (v->dy - v->dx);
			y += v->sy;
		}
		else
			v->error += 2 * v->dy;
		x++;
	}
}

void	draw_line_helper(t_data *data, t_point *p1, t_point *p2)
{
	t_line_vars	*v;

	v = data->line_vars;
	v->dx = abs(p2->x - p1->x);
	v->dy = abs(p2->y - p1->y);
	if (p1->x > p2->x)
		v->sx = -1;
	else
		v->sx = 1;
	if (v->dy < v->dx)
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