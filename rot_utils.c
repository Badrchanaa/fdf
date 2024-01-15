/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchanaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 18:38:55 by bchanaa           #+#    #+#             */
/*   Updated: 2024/01/15 18:11:59 by bchanaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_x(t_point *pt, double sin_a, double cos_a)
{
	int	z;
	int	y;

	z = pt->z;
	y = pt->y;
	pt->y = y * cos_a - z * sin_a;
	pt->z = y * sin_a - z * cos_a;
}

void	rotate_y(t_point *pt, double sin_a, double cos_a)
{
	int	x;
	int	z;

	x = pt->x;
	z = pt->z;
	pt->x = x * cos_a + z * sin_a;
	pt->z = z * cos_a - x * sin_a;
}

void	rotate_z(t_point *pt, double sin_a, double cos_a)
{
	int	x;
	int	y;

	x = pt->x;
	y = pt->y;
	pt->x = x * cos_a - y * sin_a;
	pt->y = x * sin_a + y * cos_a;
}

void	rotate_point(t_data *data, t_point *pt)
{
	rotate_x(pt, sin(DEG_TO_RAD(data->angle_x)), cos(DEG_TO_RAD(data->angle_x)));
	rotate_y(pt, sin(DEG_TO_RAD(data->angle_y)), cos(DEG_TO_RAD(data->angle_y)));
	rotate_z(pt, sin(DEG_TO_RAD(data->angle_z)), cos(DEG_TO_RAD(data->angle_z)));
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
	//rotate_map(data);
	return (0);
}