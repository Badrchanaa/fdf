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

void	color_image_point(t_data *data, int x, int y, unsigned int color)
{
	if (x >= 0 && y >= 0 && x < WIN_W && y < WIN_H)
	{
		*(unsigned int *)(data->img_addr + y * data->size_line + \
							x * (data->bits_per_pixel / 8)) = color;
	}
}

void	init_vars(t_point *p1, t_point *p2, t_line_vars *v)
{
	v->delta[0] = abs(p2->x - p1->x);
	v->delta[1] = -abs(p2->y - p1->y);
	v->inc[0] = -1;
	v->inc[1] = -1;
	if (p1->x < p2->x)
		v->inc[0] = 1;
	if (p1->y < p2->y)
		v->inc[1] = 1;
	v->err[0] = v->delta[0] + v->delta[1];
	v->coords[0] = p1->x;
	v->coords[1] = p1->y;
	v->steps[1] = fmax(v->delta[0], -v->delta[1]);
	v->steps[0] = 0;
}

void	bline(t_data *data, t_point *p1, t_point *p2, t_line_vars *v)
{
	init_vars(p1, p2, v);
	while (v->coords[0] != p2->x || v->coords[1] != p2->y)
	{
		color_image_point(data, v->coords[0], v->coords[1], \
		get_gradient_color(p1->color, p2->color, v->steps[0]++ / v->steps[1]));
		v->err[1] = 2 * v->err[0];
		if (v->err[1] >= v->delta[1])
		{
			if (v->coords[0] == p2->x)
				break ;
			v->err[0] += v->delta[1];
			v->coords[0] += v->inc[0];
		}
		if (v->err[1] <= v->delta[0])
		{
			if (v->coords[1] == p2->y)
				break ;
			v->err[0] += v->delta[0];
			v->coords[1] += v->inc[1];
		}
	}
}
