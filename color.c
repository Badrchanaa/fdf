/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchanaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 21:09:17 by bchanaa           #+#    #+#             */
/*   Updated: 2024/01/19 20:36:52 by bchanaa          ###   ########.fr       */
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
		map[i]->color = get_gradient_color(C_BLUE, C_WHITE, \
		(float)(abs(map[i]->z - data->min_z)) / (data->max_z - data->min_z));
		i++;
	}
}

unsigned int	get_color(t_uc red, t_uc green, t_uc blue, t_uc alpha)
{
	int	color;

	color = blue | (green << 8) | (red << 16) | (alpha << 24);
	return (color);
}

t_uc	get_channel_gradient(t_uc p1_channel, t_uc p2_channel, float percentage)
{
	int	channel_diff;

	channel_diff = p2_channel - p1_channel;
	return (p1_channel + round(percentage * channel_diff));
}

unsigned int	get_gradient_color(int color1, int color2, float percentage)
{
	t_uc	red;
	t_uc	green;
	t_uc	blue;

	if (color1 == color2)
		return (color1);
	red = get_channel_gradient(RED(color1), RED(color2), percentage);
	green = get_channel_gradient(GREEN(color1), GREEN(color2), percentage);
	blue = get_channel_gradient(BLUE(color1), BLUE(color2), percentage);
	return (get_color(red, green, blue, 0));
}

int	get_color_from_hex(char *hex)
{
	const char	*hex_base;
	char		conv[11];
	size_t		i;

	if (!hex || ft_strlen(hex) > 10)
		return (C_WHITE);
	i = 0;
	while (hex[i] && hex[i] != '\n')
	{
		conv[i] = ft_toupper(hex[i]);
		i++;
	}
	conv[i] = 0;
	hex_base = "0123456789ABCDEF";
	if (ft_strncmp(conv, "0X", 2) != 0 || \
		ft_strspn(conv + 2, hex_base) + 2 != i)
		return (C_WHITE);
	return (ft_atoi_base(conv + 2, hex_base, 16));
}
