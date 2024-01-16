/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchanaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 15:37:36 by bchanaa           #+#    #+#             */
/*   Updated: 2024/01/16 22:46:14 by bchanaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "fdf.h"

void	to_isometric(t_data *data, t_point *pt)
{
	int	x;
	int	y;

	x = pt->x;// MAX: map_width * cell_size, MIN: 0
	y = pt->y;// MAX: map_height * cell_size, MIN: 0
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
	pt->x = round(pt->x * data->sc_cell_size);
	pt->y = round(pt->y * data->sc_cell_size);
	pt->z = round(pt->z * data->sc_cell_size_z);
	//if (data->projection == ISOMETRIC)
	// 	to_isometric(data, pt);
	// else if (data->projection == ORTHOGRAPHIC)
	// {
		pt->x -= data->sc_cell_size * (data->map_width - 1) / 2;
		pt->y -= data->sc_cell_size * (data->map_height - 1) / 2;
	// }
	rotate_point(data, pt);
	pt->x += WIN_W_MID + data->tx;
	pt->y += WIN_H_MID + data->ty;
}