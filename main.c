/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchanaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 15:42:28 by bchanaa           #+#    #+#             */
/*   Updated: 2024/01/19 23:00:24 by bchanaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_map_details(t_data *data, t_point **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (map[i]->x < data->map_width - 1)
			map[i]->iright = i + 1;
		else
			map[i]->iright = -1;
		if (map[i]->y < data->map_height - 1)
			map[i]->ibottom = ((map[i]->y + 1) * data->map_width) + map[i]->x;
		else
			map[i]->ibottom = -1;
		i++;
	}
	data->map_w_mid = (data->map_width - 1) / 2;
	data->map_h_mid = (data->map_height - 1 ) / 2;
	data->map_ratio_mid = (data->map_width + data->map_height) / 2;
}

void	set_hooks(t_data *data)
{
	mlx_mouse_hook(data->win, handle_mouse_click, &data);
	mlx_hook(data->win, 6, 0, handle_mouse_move, &data);
	mlx_hook(data->win, 5, 0, handle_mouse_release, &data);
	mlx_do_key_autorepeaton(data->mlx);
	mlx_hook(data->win, 17, 0, close_window, &data);
	mlx_hook(data->win, 2, 0, handle_key_press, &data);
}

int	main(int argc, char **argv)
{
	t_data data;

	if (argc != 2)
		exit_wmsg(0, "Invalid args. (usage: ./fdf <map_filename>)");
	if (init_data(&data) == 1)
		exit_wmsg(errno, "Error: Memory allocation failed!");
	if (init_window(&data) != 0)
		return (EXIT_FAILURE);
	parse_landscape(argv[1], &data);
	if (!data.map)
	{
		destroy_all(&data);
		exit_wmsg(errno, "Error occured when parsing map!");
	}
	calc_cell_size(&data);
	set_hooks(&data);
	set_map_details(&data, data.map);
	init_image(&data, WIN_W, WIN_H);
	if (!data.has_color)
		set_color_scheme(1, &data);
	render(&data);
	mlx_loop(data.mlx);
	mlx_destroy_image(data.mlx, data.img);
	free_2darray((void **)data.map, true);
	mlx_destroy_window(data.mlx, data.win);
	free(data.mlx);
	return (0);
}
