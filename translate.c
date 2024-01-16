/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchanaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 16:46:40 by bchanaa           #+#    #+#             */
/*   Updated: 2024/01/16 16:15:02 by bchanaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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