/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchanaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 15:42:28 by bchanaa           #+#    #+#             */
/*   Updated: 2024/01/12 23:19:57 by bchanaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	handle_mouse_click(int button, int x, int y, void *p)
{
	static int count;
	(void)p;
	count++;
	ft_printf("[%d] x: %d y: %d button: %d.\n", count, x, y, button);
	return (0);
}

int handle_mouse_move(int x, int y, int *a)
{
	static int count;
	count++;
	printf("x: %d y: %d a: %d\n", x, y, *a);
	return (0);
}

void	destroy_all(t_data *data)
{
	if (data->mlx && data->img)
		mlx_destroy_image(data->mlx, data->img);
	if (data->mlx && data->win)
		mlx_destroy_window(data->mlx, data->win);
	free(data->mlx);
}

int close_window(t_data *data)
{
	destroy_all(data);
	free_2darray((void **)data->map, true);
	exit(EXIT_SUCCESS);	
	return (0);
}

int	handle_key_press(int keycode, t_data *data)
{
	if (keycode == 53)
		close_window(data);
	ft_printf("Keycode: %d\n", keycode);
	if (keycode >= 123 && keycode <= 126)
	{
		translate(data, keycode);
		draw_land(data);
	}
	if (keycode == 34 || keycode == 31 || keycode == 40 || keycode == 37)
	{
		handle_rotate(data, keycode);
		draw_land(data);
	}
	return (0);
}

void	isometric_projection(t_data *data)
{
	t_point	**map;
	int		x;
	int		y;
	int		i;
	int		x_offset;
	int		y_offset;

	x_offset = (WIN_H + WIN_W) / 2 -\
	((WIN_H * data->map_width) + (WIN_H * data->map_height))
	/ (4 * data->map_height);
	y_offset = 0; // - ((data->map_width * data->cell_size / 2 + data->map_height * data->cell_size / 2) + (WIN_H / 2));
	i = 0;
	map = data->map;
	if (!map)
		exit_wmsg("Error: isometric projection err\n");
	while (map[i])
	{
		x = map[i]->x;
		y = map[i]->y;
		map[i]->x = (x - y) + x_offset;
		map[i]->y = (y / 2 + x / 2) - (map[i]->z * 3) + y_offset;
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data data;

	if (argc < 2)
		exit_wmsg("Invalid arguments\n");
	init_data(&data);
	if (init_window(&data) != 0)
		return (EXIT_FAILURE);
	parse_landscape(argv[1], &data);
	if (!data.map)
	{
		destroy_all(&data);
		exit_wmsg("Error when parsing map!");
	}
	calc_cell_size(&data);
	//isometric_projection(&data);
	//mlx_mouse_hook(data.win, handle_mouse_click, &data);
	mlx_hook(data.win, 17, 0, close_window, &data);
	mlx_key_hook(data.win, handle_key_press, &data);
	init_image(&data, WIN_W, WIN_H);
	//mlx_sync(MLX_SYNC_IMAGE_WRITABLE, data.img);
	draw_land(&data);
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	//mlx_loop_hook(data->mlx, render, &data);
	mlx_loop(data.mlx);

	// Clearing
	free_2darray((void **)data.map, true);
	mlx_destroy_window(data.mlx, data.win);
	//mlx_destroy_display(data.mlx);
	free(data.mlx);
	return (0);
}