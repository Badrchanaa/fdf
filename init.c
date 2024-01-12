/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchanaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 15:48:16 by bchanaa           #+#    #+#             */
/*   Updated: 2024/01/12 22:48:20 by bchanaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	calc_cell_size(t_data *data)
{
	double	max_land_height;
	int		i;
	t_point	**map;

	max_land_height = WIN_H;
	data->cell_size = (((int)max_land_height) / data->map_height) / 2;
	i = 0;
	map = data->map;
	while (map[i])
	{
		map[i]->x = map[i]->x * data->cell_size;
		map[i]->y = map[i]->y * data->cell_size;
		i++;
	}
}

void	init_data(t_data *data)
{
	data->img = NULL;
	data->img_addr = NULL;
	data->mlx = NULL;
	data->win = NULL;
	data->scale = 1;
	data->tx = 0;
	data->angle_x = 0;
	data->angle_y = 0;
	data->angle_z = 0;
	data->ty = 0;
}

int	init_window(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		return (EXIT_FAILURE);
	data->win = mlx_new_window(data->mlx, WIN_W, WIN_H, WINDOW_TITLE);
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