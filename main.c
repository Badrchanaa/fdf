/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchanaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 15:42:28 by bchanaa           #+#    #+#             */
/*   Updated: 2024/01/14 23:43:09 by bchanaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	destroy_all(t_data *data)
{
	if (data->mlx && data->img)
		mlx_destroy_image(data->mlx, data->img);
	if (data->mlx && data->win)
		mlx_destroy_window(data->mlx, data->win);
	free(data->draw_p1);
	free(data->draw_p2);
	free(data->mlx);
}

int close_window(t_data *data)
{
	destroy_all(data);
	free_2darray((void **)data->map, true);
	exit(EXIT_SUCCESS);	
	return (0);
}

void	isometric_projection(t_data *data)
{
	t_point	**map;
	int		x;
	int		y;
	int		i;
	//int		x_offset;
	//int		y_offset;

	//x_offset = (WIN_H + WIN_W) / 2 -\
	//((WIN_H * data->map_width) + (WIN_H * data->map_height))
	/// (4 * data->map_height);
	//y_offset = 0; // - ((data->map_width * data->cell_size / 2 + data->map_height * data->cell_size / 2) + (WIN_H / 2));
	i = 0;
	map = data->map;
	if (!map)
		exit_wmsg("Error: isometric projection error, map is null.\n");
	while (map[i])
	{
		x = map[i]->x;
		y = map[i]->y;
		map[i]->x = (x - y);
		map[i]->y = (y / 2 + x / 2) - (map[i]->z * 3);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data data;

	if (argc < 2)
		exit_wmsg("Invalid arguments\n");
	if (init_data(&data) == 1)
		exit_wmsg("Error: Memory allocation failed!\n");
	if (init_window(&data) != 0)
		return (free(data.draw_p1), free(data.draw_p2), EXIT_FAILURE);
	parse_landscape(argv[1], &data);
	ft_printf("height: %d\n", data.map_height);
	if (!data.map)
	{
		destroy_all(&data);
		exit_wmsg("Error occured when parsing map!\n");
	}
	calc_cell_size(&data);
	ft_printf("Min_z: %d Max_z: %d\n", data.min_z, data.max_z);
	//isometric_projection(&data);
	mlx_mouse_hook(data.win, handle_mouse_click, &data);
	mlx_hook(data.win, 6, 0, handle_mouse_move, &data);
	mlx_hook(data.win, 5, 0, handle_mouse_release, &data);
	mlx_do_key_autorepeaton(data.mlx);
	mlx_hook(data.win, 17, 0, close_window, &data);
	mlx_hook(data.win, 2, 0, handle_key_press, &data);
	draw_info(&data);
	//mlx_key_hook(data.win, handle_key_press, &data);
	init_image(&data, WIN_W, WIN_H);
	//mlx_sync(MLX_SYNC_IMAGE_WRITABLE, data.img);
	render(&data);
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	//mlx_loop_hook(data->mlx, render, &data);~
	mlx_loop(data.mlx);

	// Clearing
	free_2darray((void **)data.map, true);
	free(data.draw_p1);
	free(data.draw_p2);
	mlx_destroy_window(data.mlx, data.win);
	//mlx_destroy_display(data.mlx);
	free(data.mlx);
	return (0);
}
