/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchanaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 15:48:16 by bchanaa           #+#    #+#             */
/*   Updated: 2024/01/19 18:51:04 by bchanaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	calc_cell_size(t_data *data)
{
	int	diff;

	data->cell_size = (WIN_H / data->map_height) / 1.5;
	if (data->cell_size == 0)
		data->cell_size = 1;
	data->sc_cell_size = data->cell_size * data->scale;
	diff = abs(data->max_z - data->min_z);
	data->cell_size_z = fmin(1, (float)WIN_H / (2 * diff));
	data->sc_cell_size_z = data->cell_size_z * data->scale;
}

int	init_data(t_data *data)
{
	ft_memset(data, 0, sizeof(t_data));
	data->scale = 1;
	data->projection = DEFAULT_PROJECTION;
	data->cell_size = 1;
	data->cell_size_z = 1;
	data->min_z = INT_MAX;
	data->max_z = INT_MIN;
	return (0);
}

void	reset_data(t_data *data)
{
	data->scale = 1;
	calc_cell_size(data);
	ft_memset(&data->tx, 0, sizeof(int) * 5);
	ft_memset(&data->angle_x, 0, sizeof(float) * 3);
}

int	init_window(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		return (EXIT_FAILURE);
	data->win = mlx_new_window(data->mlx, WIN_W, WIN_H, WINDOW_TITLE);
	if (!data->win)
		return (free(data->mlx), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int init_image(t_data *data, int img_width, int img_height)
{
	data->img = mlx_new_image(data->mlx, img_width, img_height);
	data->img_addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->size_line, &data->endian);
	return (0);
}