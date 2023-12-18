/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchanaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 18:09:28 by bchanaa           #+#    #+#             */
/*   Updated: 2023/12/16 13:32:53 by bchanaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


int	get_color(unsigned char red, unsigned char green,
			unsigned char blue, unsigned char alpha)
{
	int	color;

	color = (blue) | (green << 8) | (red << 16) | (alpha << 24);
	return (color);
}
