/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchanaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 18:38:55 by bchanaa           #+#    #+#             */
/*   Updated: 2024/01/13 21:25:21 by bchanaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_x(t_point *pt, double sin_a, double cos_a)
{
	pt->y = pt->y * cos_a - pt->z * sin_a;
	pt->z = pt->y * sin_a - pt->z * cos_a;
}

void	rotate_y(t_point *pt, double sin_a, double cos_a)
{
	pt->x = pt->x * cos_a + pt->z * sin_a;
	pt->z = pt->z * cos_a - pt->x * sin_a;
}

void	rotate_z(t_point *pt, double sin_a, double cos_a)
{
	pt->x = pt->x * cos_a - pt->y * sin_a;
	pt->y = pt->x * sin_a + pt->y * cos_a;
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