/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchanaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 20:51:03 by bchanaa           #+#    #+#             */
/*   Updated: 2023/12/21 23:49:31 by bchanaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	color_image_point(t_data *data, int x, int y, int color)
{
	char	*pixel;
	int		pos;

	pos = y * data->size_line + x * (data->bits_per_pixel / 8);
	//ft_printf("pos: %d\n", pos);
	pixel = data->img_addr + pos;
	*(unsigned int *)pixel = color;
}

void	draw_line(t_data *data, t_point *p1, t_point *p2)
{
	int		i;
	int		cx;
	int		cy;

	i = 0;
	//ft_printf("p1->x: %10d p1->y: %10d | p2->x: %10d p2->y: %10d\n", p1->x, p1->y, p2->x, p2->y);
	//printf("		dx: %13d dy: %14d | distance: %13f\n\n", dx, dy, distance);

	// !! change this back to work for non diagonal/aligned points !!
	// !! add gradient color between the points !!
	while (i < data->cell_size)
	{
		cx = p1->x * data->cell_size;
		if (p1->x != p2->x)
			cx += i;
		cy = p1->y * data->cell_size;
		if (p1->y != p2->y)
			cy += i;
		//printf("nx: %d ny: %d\n", (p1->x * data->cell_size_x) + (int)(round(dx / distance * i)), (p1->y * data->cell_size_x) + (int)(round(dy / distance * i)));
		color_image_point(data, cx, cy, p1->color);
		i++;
	}
}