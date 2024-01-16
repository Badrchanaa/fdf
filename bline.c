/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchanaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 23:42:45 by bchanaa           #+#    #+#             */
/*   Updated: 2024/01/15 23:55:51 by bchanaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static inline void	draw_vertical_line(t_data *data, t_point *p1, t_point *p2)
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
	dist = abs(p1->y - p2->y);
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
	t_point	*tmp;

	if (p1->x > p2->x)
	{
		tmp = p1;
		p1 = p2;
		p2 = tmp;
	}
	dist = abs(p1->x - p2->x);
	i = 0;
	while (p1->x + i <= p2->x)
	{
		
		p_color = get_gradient_color(p1->color, p2->color, i / (double)dist);
		color_image_point(data, p1->x + i, p1->y, p_color);
		i++;
	}
}

void	bline(t_data *data, t_point *p1, t_point *p2)
{
	t_line_vars			*lv;
	register int		x;
	register int		y;
	int					color;
	int					e2;
	bool				should_draw;

	should_draw = false;
	if (p1->x == p2->x && p1->y == p2->y)
		color_image_point(data, p1->x, p1->y, p1->color);
	else if (p1->y == p2->y)
		draw_horizontal_line(data, p1, p2);
	else if (p1->x == p2->x)
		draw_vertical_line(data, p1, p2);
	else
		should_draw = true;
	if (!should_draw)
		return;
	lv = data->line_vars;
	lv->dx = abs(p2->x - p1->x);
	lv->dy = -abs(p2->y - p1->y);
	if (p1->x < p2->x)
		lv->sx = 1;
	else
		lv->sx = -1;
	if (p1->y < p2->y)
		lv->sy = 1;
	else
		lv->sy = -1;
	lv->error = lv->dx + lv->dy;
	x = p1->x;
	y = p1->y;
	lv->steps = fmax(lv->dx, -lv->dy);
	lv->steps_i = 0;
	while (1)
	{
		color = get_gradient_color(p1->color, p2->color, (double)lv->steps_i++ / lv->steps);
		color_image_point(data, x, y, color);
		if (x == p2->x && y == p2->y)
			break;
		e2 = 2 * lv->error;
		if (e2 >= lv->dy)
		{
			if (x == p2->x)
				break;
			lv->error += lv->dy;
			x += lv->sx;
		}
		if (e2 <= lv->dx)
		{
			if (y == p2->y)
				break;
			lv->error += lv->dx;
			y += lv->sy;
		}
	}
}
