/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchanaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 16:46:40 by bchanaa           #+#    #+#             */
/*   Updated: 2024/01/13 18:46:32 by bchanaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	translate_point(t_data *data, t_point *pt)
{
	pt->x += WIN_W / 2 + data->tx;
	pt->y += WIN_H / 2 + data->ty;
}

int	handle_translate(t_data *data, int keycode)
{
	if (!data)
		return (1);
	if (keycode == 123) // Left
		data->tx += -TR_FACTOR;
	else if (keycode == 124) // Right
		data->tx += TR_FACTOR;
	else if (keycode == 125) // Down
		data->ty += TR_FACTOR;
	else if (keycode == 126)
		data->ty += -TR_FACTOR;
	return (0);
}