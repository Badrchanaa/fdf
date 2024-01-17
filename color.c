/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchanaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 21:09:17 by bchanaa           #+#    #+#             */
/*   Updated: 2024/01/17 21:03:55 by bchanaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_color_scheme(t_uc scheme, t_data *data)
{
	t_point	**map;
	int		i;
	int		range;
	range = data->max_z - data->min_z;
	if (range == 0)
		return ;
	(void)scheme;
	i = 0;
	map = data->map;
	while (map[i])
	{
		map[i]->color = get_gradient_color(C_BLUE, C_WHITE, (double)(abs(map[i]->z - data->min_z)) / (data->max_z - data->min_z));
		i++;
	}
}