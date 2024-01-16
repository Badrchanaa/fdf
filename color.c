/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchanaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 21:09:17 by bchanaa           #+#    #+#             */
/*   Updated: 2024/01/16 21:25:45 by bchanaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_color_scheme(t_uc scheme, t_data *data)
{
	register t_point	**map;
	int					base_color;
	int					i;
	int					range;

	range = data->max_z - data->min_z;
	base_color = 0x4060ff;
	if (range == 0)
		return ;
	(void)scheme;
	i = 0;
	map = data->map;
	while (map[i])
	{
		map[i]->color = get_gradient_color(base_color, C_WHITE, (double)(abs(map[i]->z - data->min_z)) / (data->max_z - data->min_z));
		i++;
	}
}