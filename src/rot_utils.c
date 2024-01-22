/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchanaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 18:38:55 by bchanaa           #+#    #+#             */
/*   Updated: 2024/01/20 16:11:52 by bchanaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_x(int *y, int *z, float *angle)
{
	int	prev_y;

	prev_y = *y;
	*y = prev_y * cos(*angle) - *z * sin(*angle);
	*z = prev_y * sin(*angle) + *z * cos(*angle);
}

void	rotate_y(int *x, int *z, float *angle)
{
	int	prev_x;

	prev_x = *x;
	*x = prev_x * cos(*angle) + *z * sin(*angle);
	*z = *z * cos(*angle) - prev_x * sin(*angle);
}

void	rotate_z(int *x, int *y, float *angle)
{
	int	prev_x;

	prev_x = *x;
	*x = prev_x * cos(*angle) - *y * sin(*angle);
	*y = prev_x * sin(*angle) + *y * cos(*angle);
}

int	handle_rotate(t_data *data, int keycode)
{
	if (keycode == XK_i)
		data->angle_x -= ANGLE_FACTOR;
	else if (keycode == XK_o)
		data->angle_x += ANGLE_FACTOR;
	else if (keycode == XK_k)
		data->angle_y -= ANGLE_FACTOR;
	else if (keycode == XK_l)
		data->angle_y += ANGLE_FACTOR;
	else if (keycode == XK_m)
		data->angle_z -= ANGLE_FACTOR;
	else if (keycode == XK_n)
		data->angle_z += ANGLE_FACTOR;
	return (0);
}
