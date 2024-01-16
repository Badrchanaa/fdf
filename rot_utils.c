/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchanaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 18:38:55 by bchanaa           #+#    #+#             */
/*   Updated: 2024/01/16 22:16:46 by bchanaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_x(t_point *pt, double sin_a, double cos_a)
{
	register int	z;
	register int	y;

	z = pt->z;
	y = pt->y;
	pt->y = y * cos_a - z * sin_a;
	pt->z = y * sin_a - z * cos_a;
}

void	rotate_y(t_point *pt, double sin_a, double cos_a)
{
	register int	x;
	register int	z;

	x = pt->x;
	z = pt->z;
	pt->x = x * cos_a + z * sin_a;
	pt->z = z * cos_a - x * sin_a;
}

void	rotate_z(t_point *pt, double sin_a, double cos_a)
{
	register int	x;
	register int	y;

	x = pt->x;
	y = pt->y;
	pt->x = x * cos_a - y * sin_a;
	pt->y = x * sin_a + y * cos_a;
}

void	rotate_point(t_data *data, t_point *pt)
{
	rotate_z(pt, data->sin_z, data->cos_z);
	rotate_x(pt, data->sin_x, data->cos_x);
	rotate_y(pt, data->sin_y, data->cos_y);
}

int	handle_rotate(t_data *data, int keycode)
{
	if (keycode == 34) // i: decrease angle
		data->angle_x -= ANGLE_FACTOR;
	else if (keycode == 31) // o: increase angle
		data->angle_x += ANGLE_FACTOR;
	else if (keycode == 40)
		data->angle_y -= ANGLE_FACTOR;
	else if (keycode == 37)
		data->angle_y += ANGLE_FACTOR;
	else if (keycode == 45)
		data->angle_z -= ANGLE_FACTOR;
	else if (keycode == 46)
		data->angle_z += ANGLE_FACTOR;
	data->cos_x = cos(data->angle_x);
	data->sin_x = sin(data->angle_x);
	data->cos_y = cos(data->angle_y);
	data->sin_y = sin(data->angle_y);
	data->cos_z = cos(data->angle_z);
	data->sin_z = sin(data->angle_z);
	//rotate_map(data);
	return (0);
}