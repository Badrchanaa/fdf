/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchanaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 15:37:36 by bchanaa           #+#    #+#             */
/*   Updated: 2024/01/19 23:31:51 by bchanaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	handle_height_scale(t_data *data, int keycode)
{
	if (keycode == 43)
	{
		data->cell_size_z *= 1 - ZOOM_FACTOR;
		data->sc_cell_size_z = data->cell_size_z * data->scale;
	}
	else
	{
		data->cell_size_z *= 1 + ZOOM_FACTOR;
		data->sc_cell_size_z = data->cell_size_z * data->scale;
	}
}

void	to_isometric(t_data *data, int *x, int *y, int *z)
{
	int	prev_x;

	prev_x = *x;
	*x += *y;
	*y = (*y / 2 - prev_x / 2) - *z;
	*x -= data->sc_cell_size * data->map_ratio_mid;
}

void	switch_projection(t_data *data)
{
	if (data->projection == ISOMETRIC)
		data->projection = ORTHOGRAPHIC;
	else
		data->projection = ISOMETRIC;
	reset_data(data);
}

// Applies all transformations to a point such as rotation, translation and zoom
t_point	transform(t_data *data, t_point *pt)
{
	t_point	npt;

	npt.x = pt->x * data->sc_cell_size;
	npt.y = pt->y * data->sc_cell_size;
	npt.z = pt->z * data->sc_cell_size_z;
	npt.color = pt->color;
	if (data->projection == ISOMETRIC)
		to_isometric(data, &npt.x, &npt.y, &npt.z);
	else if (data->projection == ORTHOGRAPHIC)
	{
		npt.x -= data->sc_cell_size * data->map_w_mid;
		npt.y -= data->sc_cell_size * data->map_h_mid;
	}
	rotate_x(&npt.y, &npt.z, &data->angle_x);
	rotate_y(&npt.x, &npt.z, &data->angle_y);
	rotate_z(&npt.x, &npt.y, &data->angle_z);
	npt.x += WIN_W_MID + data->tx;
	npt.y += WIN_H_MID + data->ty;
	return (npt);
}
