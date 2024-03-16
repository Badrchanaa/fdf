/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchanaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 22:24:46 by bchanaa           #+#    #+#             */
/*   Updated: 2024/01/22 19:19:08 by bchanaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	handle_translate(t_data *data, int keycode)
{
	if (!data)
		return (1);
	if (keycode == XK_Left)
		data->tx += -TR_FACTOR;
	else if (keycode == XK_Right)
		data->tx += TR_FACTOR;
	else if (keycode == XK_Down)
		data->ty += TR_FACTOR;
	else if (keycode == XK_Up)
		data->ty += -TR_FACTOR;
	return (0);
}

int	handle_key_press(int keycode, t_data *data)
{
	ft_printf("key: %d\n", keycode);
	bool	should_render;

	should_render = true;
	if (data->is_locked)
		return (0);
	if (keycode == XK_Escape)
		close_window(data);
	else if (keycode == XK_Right || keycode == XK_Left || keycode == XK_Up || keycode == XK_Down)
		handle_translate(data, keycode);
	else if (keycode == XK_o || keycode == XK_i || keycode == XK_k || \
			keycode == XK_l || keycode == XK_n || keycode == XK_m)
		handle_rotate(data, keycode);
	else if (keycode == XK_s)
		switch_projection(data);
	else if (keycode == XK_r)
		reset_data(data);
	else if (keycode == XK_less || keycode == XK_greater)
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
