/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchanaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 16:19:32 by bchanaa           #+#    #+#             */
/*   Updated: 2023/12/21 23:48:38 by bchanaa          ###   ########.fr       */
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
	perror(msg);
	exit(EXIT_FAILURE);
}

int	get_color(unsigned char red, unsigned char green,
			unsigned char blue, unsigned char alpha)
{
	int	color;

	color = (blue) | (green << 8) | (red << 16) | (alpha << 24);
	return (color);
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