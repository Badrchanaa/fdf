/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchanaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 15:42:28 by bchanaa           #+#    #+#             */
/*   Updated: 2023/12/21 23:45:48 by bchanaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
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
	if (data->mlx && data->win)
		mlx_destroy_window(data->mlx, data->win);
	free(data->mlx);
}

int	handle_key_press(int keycode, t_data *data)
{
	(void)data;
	ft_printf("key %d is pressed!\n", keycode);
	return (0);
}

int close_window(t_data *data)
{
	destroy_all(data);
	free_2darray((void **)data->map, true);
	exit(EXIT_SUCCESS);	
	return (0);
}

int draw_land(t_data *data)
{
	int		i;
	t_point	**map;
	t_point	*curr_pt;

	i = 0;
	ft_printf("drawing land w: %d h: %d\n", data->map_width, data->map_height);
	init_image(data, WINDOW_WIDTH, WINDOW_HEIGHT);
	map = data->map;
	while (map[i])
	{
		curr_pt = map[i];
		if (curr_pt->x < data->map_width - 1)
			draw_line(data, curr_pt, map[i + 1]);
		if (curr_pt->y < data->map_height - 1)
			draw_line(data, curr_pt, map[((curr_pt->y + 1) * data->map_width) + curr_pt->x]);
		i++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
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
	//mlx_mouse_hook(data.win, handle_mouse_click, &data);
	mlx_hook(data.win, 17, 0, close_window, &data);
	mlx_key_hook(data.win, handle_key_press, &data);
	draw_land(&data);
	//mlx_loop_hook(data->mlx, render, &data);
	mlx_loop(data.mlx);

	// Clearing
	free_2darray((void **)data.map, true);
	mlx_destroy_window(data.mlx, data.win);
	//mlx_destroy_display(data.mlx);
	free(data.mlx);
	return (0);
}
