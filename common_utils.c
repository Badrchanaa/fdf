/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchanaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 16:19:32 by bchanaa           #+#    #+#             */
/*   Updated: 2024/01/13 22:33:36 by bchanaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	count_split(char *str, char c)
{
	int		is_empty;
	int		count;

	count = 0;
	is_empty = 1;
	while (*str)
	{
		if (*str == c && !is_empty)
		{
			count++;
			is_empty = 1;
		}
		if (*str != c && is_empty)
			is_empty = 0;
		str++;
	}
	if (!is_empty)
		count++;
	return (count);
}

void	free_2darray(void **arr, bool free_root_p)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	if (free_root_p)
		free(arr);
}

void	exit_wmsg(const char *msg)
{
	ft_printf(msg);
	exit(0);
}

unsigned int	get_color(t_uc red, t_uc green, t_uc blue, t_uc alpha)
{
	int	color;

	color = blue | (green << 8) | (red << 16) | (alpha << 24);
	return (color);
}

// t_uc	get_red(int color)
// {
// 	return ((color & (255 << 16)) >> 16);
// }

// t_uc	get_green(int color)
// {
// 	return ((color & (255 << 8)) >> 8);
// }

// t_uc	get_blue(int color)
// {
// 	return (color & 255);
// }

t_uc	get_channel_gradient(t_uc p1_channel, t_uc p2_channel, double percentage)
{
	int	channel_diff;

	channel_diff = p2_channel - p1_channel;
	return (p1_channel + round(percentage * channel_diff));
}

unsigned int get_gradient_color(int color1, int color2, double percentage)
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

// !! change so it works for hex colors of size {4, 6, 8} with upper/lower hex base !!
int	get_color_from_hex(char *hex)
{
	const char		*hex_base;

	hex_base = "0123456789ABCDEF";
	if (!hex || ft_strspn(hex + 2, hex_base) + 2 != 8 || ft_strncmp(hex, "0x", 2) != 0)
		return (C_WHITE);
	return ft_atoi_base(hex + 2, hex_base, 16);	
}