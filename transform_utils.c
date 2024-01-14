/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchanaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 15:37:36 by bchanaa           #+#    #+#             */
/*   Updated: 2024/01/14 16:57:41 by bchanaa          ###   ########.fr       */
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
	ft_memset(&(data->tx), 0, sizeof(int) * 5); // reset translation and rotation
}

void	transform_point(t_data *data, t_point *pt)
{
	pt->x = pt->x * data->sc_cell_size;
	pt->y = pt->y * data->sc_cell_size;
	pt->z = pt->z * data->cell_size_z;
	if (data->projection == ISOMETRIC)
		to_isometric(data, pt);
	else if (data->projection == ORTHOGRAPHIC)
	{
		pt->x -= data->sc_cell_size * data->map_width / 2;
		pt->y -= data->sc_cell_size * data->map_height / 2;
	}
	rotate_point(data, pt);
	translate_point(data, pt);
}