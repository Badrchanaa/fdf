/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchanaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 18:38:55 by bchanaa           #+#    #+#             */
/*   Updated: 2024/01/12 23:31:40 by bchanaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_x(t_point *pt, double sin_a, double cos_a)
{
	pt->y = pt->y * cos_a;// - pt->z * sin_a;
	(void)sin_a;
	//pt->z = pt->y * sin_a - pt->z * cos_a;
}

void	rotate_y(t_point *pt, double sin_a, double cos_a)
{
	pt->x = pt->x * cos_a; //+ pt->z * sin_a;
	pt->z = pt->z * cos_a - pt->x * sin_a;
}

t_point	*rotate_point(t_data *data, t_point *pt)
{
	t_point	*new_pt;

	new_pt = malloc(sizeof(t_point));
	if (!new_pt)
	{
		ft_printf("couldnt allocate new_pt\n");
		return (NULL);
	}
	new_pt->x = pt->x - (data->cell_size * data->map_width / 2) - data->tx;
	new_pt->y = pt->y - (data->cell_size * data->map_height / 2) - data->ty;
	new_pt->z = pt->z;
	new_pt->color = pt->color;
	rotate_x(new_pt, sin(DEG_TO_RAD(data->angle_x)), cos(DEG_TO_RAD(data->angle_x)));
	rotate_y(new_pt, sin(DEG_TO_RAD(data->angle_y)), cos(DEG_TO_RAD(data->angle_y)));
	new_pt->x += (data->cell_size * data->map_width / 2) + data->tx;
	new_pt->y += (data->cell_size * data->map_height / 2) + data->ty;
	return (new_pt);
}

int	handle_rotate(t_data *data, int keycode)
{
	if (keycode == 34) // i: decrease angle
		data->angle_x -= 15;
	else if (keycode == 31) // o: increase angle
		data->angle_x += 15;
	else if (keycode == 40)
		data->angle_y -= 15;
	else if (keycode == 37)
		data->angle_y += 15;
	//rotate_map(data);
	return (0);
}