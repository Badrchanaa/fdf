/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchanaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 22:24:46 by bchanaa           #+#    #+#             */
/*   Updated: 2024/01/19 23:49:11 by bchanaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	handle_key_press(int keycode, t_data *data)
{
	bool	should_render;

	should_render = true;
	if (keycode == 53)
		close_window(data);
	else if (keycode >= 123 && keycode <= 126)
		handle_translate(data, keycode);
	else if (keycode == 34 || keycode == 31 || keycode == 40 || \
			keycode == 37 || keycode == 45 || keycode == 46)
		handle_rotate(data, keycode);
	else if (keycode == 1)
		switch_projection(data);
	else if (keycode == 15)
		reset_data(data);
	else if (keycode == 43 || keycode == 47)
		handle_height_scale(data, keycode);
	else
		should_render = false;
	if (should_render)
		render(data);
	return (0);
}

int	handle_mouse_release(int button, int x, int y, t_data *data)
{
	if (button == 1)
		data->is_dragging = false;
	(void)data;
	(void)x;
	(void)y;
	return (0);
}

int	handle_mouse_move(int x, int y, t_data *data)
{
	if (!data->is_dragging)
		return (0);
	data->tx -= data->mouse_x - x;
	data->ty -= data->mouse_y - y;
	data->mouse_x = x;
	data->mouse_y = y;
	render(data);
	return (0);
}

int	handle_mouse_click(int button, int x, int y, t_data *data)
{
	float	scale;

	scale = data->scale;
	if (button == 5 && scale < ZOOM_MAX)
		data->scale += ZOOM_FACTOR;
	else if (button == 4 && scale > ZOOM_MIN)
		data->scale -= ZOOM_FACTOR;
	if (data->scale != scale)
	{
		data->sc_cell_size = data->cell_size * data->scale;
		data->sc_cell_size_z = data->cell_size_z * data->scale;
		render(data);
	}
	if (button == 1)
	{
		data->is_dragging = true;
		data->mouse_x = x;
		data->mouse_y = y;
	}
	return (0);
}
