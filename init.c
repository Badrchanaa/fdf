/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchanaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 15:48:16 by bchanaa           #+#    #+#             */
/*   Updated: 2024/01/17 22:12:45 by bchanaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	calc_cell_size(t_data *data)
{
	data->cell_size = (WIN_H / data->map_height) / 2;
	if (data->cell_size == 0)
		data->cell_size = 1;
	data->sc_cell_size = data->cell_size * data->scale;
	data->sc_cell_size_z = data->cell_size_z * data->scale;
}

int	init_data(t_data *data)
{
	ft_memset(data, 0, sizeof(t_data));
	data->draw_p1 = malloc(sizeof(t_point));
	data->draw_p2 = malloc(sizeof(t_point));
	data->line_vars = malloc(sizeof(t_line_vars));
	if (!data->draw_p1 || !data->draw_p2 || !data->line_vars)
		return (free_data(data), 1);
	data->scale = 1;
	data->projection = DEFAULT_PROJECTION;
	
	data->cell_size = 1;
	data->cell_size_z = 1;
	data->min_z = INT_MAX;
	data->max_z = INT_MIN;
	// if (DEFAULT_PROJECTION == ISOMETRIC)
	// {
	// 	data->angle_x = 0.955316618;
	// 	data->angle_y = DEG_TO_RAD(0);
	// 	data->angle_z = DEG_TO_RAD(45);
	// 	handle_rotate(data, 0);
	// }
	// else
	// {
		data->cos_x = 1;
		data->cos_y = 1;
		data->cos_z = 1;
	// }
	return (0);
}

void	reset_data(t_data *data)
{
	data->scale = 1;
	data->sc_cell_size = data->cell_size;
	ft_memset(&data->tx, 0, sizeof(int) * 5);
	ft_memset(&data->angle_x, 0, sizeof(double) * 3);
	data->cos_x = 1;
	data->cos_y = 1;
	data->cos_z = 1;
	ft_memset(&data->sin_x, 0, sizeof(double) * 3);
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