/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchanaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 15:24:09 by bchanaa           #+#    #+#             */
/*   Updated: 2024/01/19 22:24:49 by bchanaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	destroy_all(t_data *data)
{
	if (data->mlx && data->img)
		mlx_destroy_image(data->mlx, data->img);
	if (data->mlx && data->win)
		mlx_destroy_window(data->mlx, data->win);
	free(data->mlx);
}

int	close_window(t_data *data)
{
	destroy_all(data);
	if (data && data->map)
		free_2darray((void **)data->map, true);
	exit(EXIT_SUCCESS);
	return (0);
}
