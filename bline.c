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

void	bline(t_data *data, t_point *p1, t_point *p2)
{
	t_line_vars	*lv;
	int		x;
	int		y;
	int		color;
	int		e2;

	lv = data->line_vars;
	lv->dx = abs(p2->x - p1->x);
	lv->dy = abs(p2->y - p1->y);
	if (p1->x < p2->x)
		lv->sx = 1;
	else
		lv->sx = -1;
	lv->error = lv->dx + lv->dy;
	while (x != p2->x && y != p1->x)
	{
		color_image_point(data, x, y, color);
		e2 = 2 * error;
		if (e2 >= lv->dy)
		{
			if (x == p2->x)
				break;
			error = error + dy;
			x += lv->sx;
		}
		if (e2 <= lv->dx)
		{
			if (y == p2->y)
				break;
			error = error + lv->dx;
			y += lv->sy;
		}
	}
}
