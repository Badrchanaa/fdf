/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchanaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 16:46:40 by bchanaa           #+#    #+#             */
/*   Updated: 2024/01/12 18:21:41 by bchanaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	translate_map(t_data *data)
{
	int		i;
	t_point	**map;

	i = 0;
	ft_printf("translating tx: %d ty: %d\n", data->tx, data->ty);
	map = data->map;
	while(map[i])
	{
		map[i]->x += data->tx;
		map[i]->y += data->ty;
		i++;
	}
}

int	translate(t_data *data, int keycode)
{
	if (!data)
		return (1);
	data->tx = 0;
	data->ty = 0;
	if (keycode == 123) // Left
		data->tx = -TR_FACTOR;
	else if (keycode == 124) // Right
		data->tx = TR_FACTOR;
	else if (keycode == 125) // Down
		data->ty = TR_FACTOR;
	else if (keycode == 126)
		data->ty = -TR_FACTOR;
	translate_map(data);
	return (0);
}