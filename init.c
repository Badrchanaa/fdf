/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchanaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 15:48:16 by bchanaa           #+#    #+#             */
/*   Updated: 2024/01/14 23:47:15 by bchanaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	calc_cell_size(t_data *data)
{
	data->cell_size = (WIN_H / data->map_height) / 2;
	data->sc_cell_size = data->cell_size * data->scale;
}

int	init_data(t_data *data)
{
	ft_memset(data, 0, sizeof(t_data));
	data->draw_p1 = malloc(sizeof(t_point));
	data->draw_p2 = malloc(sizeof(t_point));
	if (!data->draw_p1 || !data->draw_p2)
		return (free(data->draw_p1), free(data->draw_p2), 1);
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
	ft_memset(&data->tx, 0, sizeof(int) * 5);
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