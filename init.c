/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchanaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 15:48:16 by bchanaa           #+#    #+#             */
/*   Updated: 2023/12/21 23:52:02 by bchanaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"

void	calc_cell_size(t_data *data)
{
	double	max_land_height;
	// update so it generates appropriate cell_size depending on map size (probably adjust window size too)
	max_land_height = WINDOW_HEIGHT * 0.75;
	data->cell_size = ((int)max_land_height) / data->map_height;
}

void	init_data(t_data *data)
{
	data->img = NULL;
	data->img_addr = NULL;
	data->mlx = NULL;
	data->win = NULL;
	data->scale = 1;
}

int	init_window(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		return (EXIT_FAILURE);
	data->win = mlx_new_window(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
	if (!data->win)
	{
		//mlx_destroy_display(data->mlx); no prototype for this function ???
		return (free(data->mlx), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int init_image(t_data *data, int img_width, int img_height)
{
	data->img = mlx_new_image(data->mlx, img_width, img_height);
	data->img_addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->size_line, &data->endian);
	return (0);
}