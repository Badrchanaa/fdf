/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchanaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 15:24:09 by bchanaa           #+#    #+#             */
/*   Updated: 2024/01/19 22:04:39 by bchanaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_data(t_data *data)
{
	if (!data)
		return ;
	if (data->mlx)
		free(data->mlx);
}

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
	free_2darray((void **)data->map, true);
	exit(EXIT_SUCCESS);
	return (0);
}
