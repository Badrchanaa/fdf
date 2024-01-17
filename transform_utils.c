/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchanaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 15:37:36 by bchanaa           #+#    #+#             */
/*   Updated: 2024/01/17 22:08:35 by bchanaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "fdf.h"

void	to_isometric(t_data *data, t_point *pt)
{
	int	x;
	int	y;

	x = pt->x;
	y = pt->y;
	pt->x = x + y;
	pt->y = (y / 2 - x / 2) - pt->z;
	pt->x -= data->sc_cell_size * (data->map_width + data->map_height) / 2;
}

void	switch_projection(t_data *data)
{
	if (data->projection == ISOMETRIC)
		data->projection = ORTHOGRAPHIC;
	else
		data->projection = ISOMETRIC;
	reset_data(data);
}

void	transform_point(t_data *data, t_point *pt)
{
	pt->x = pt->x * data->sc_cell_size;
	pt->y = pt->y * data->sc_cell_size;
	pt->z = pt->z * data->sc_cell_size_z;
	if (data->projection == ISOMETRIC)
		to_isometric(data, pt);
	else if (data->projection == ORTHOGRAPHIC)
	{
		pt->x -= data->sc_cell_size * data->map_w_mid;
		pt->y -= data->sc_cell_size * data->map_h_mid;
	}
	rotate_point(data, pt);
	pt->x += WIN_W_MID + data->tx;
	pt->y += WIN_H_MID + data->ty;
}
