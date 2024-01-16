/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchanaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 15:42:28 by bchanaa           #+#    #+#             */
/*   Updated: 2024/01/16 22:19:49 by bchanaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main2(int argc, char **argv)
{
	t_data data;

	if (argc < 2)
		exit_wmsg("Invalid arguments\n");
	if (init_data(&data) == 1)
		exit_wmsg("Error: Memory allocation failed!\n");
	if (init_window(&data) != 0)
		return (free_data(&data), EXIT_FAILURE);
	parse_landscape(argv[1], &data);
	//ft_printf("height: %d\n", data.map_height);
	if (!data.map)
	{
		destroy_all(&data);
		exit_wmsg("Error occured when parsing map!\n");
	}
	calc_cell_size(&data);
	ft_printf("width: %d height: %d min_z: %d Max_z: %d\n", data.map_width, data.map_height, data.min_z, data.max_z);
	//isometric_projection(&data);
	mlx_mouse_hook(data.win, handle_mouse_click, &data);
	mlx_hook(data.win, 6, 0, handle_mouse_move, &data);
	mlx_hook(data.win, 5, 0, handle_mouse_release, &data);
	mlx_do_key_autorepeaton(data.mlx);
	mlx_hook(data.win, 17, 0, close_window, &data);
	mlx_hook(data.win, 2, 0, handle_key_press, &data);
	//mlx_key_hook(data.win, handle_key_press, &data);
	init_image(&data, WIN_W, WIN_H);
	//mlx_sync(MLX_SYNC_IMAGE_WRITABLE, data.img);
	set_color_scheme(1, &data);
	
	render(&data);
	//mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
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

int main(int ac, char *av[])
{
	main2(ac, av);
	return (0);
}
