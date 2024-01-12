/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchanaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 19:55:05 by bchanaa           #+#    #+#             */
/*   Updated: 2023/11/06 18:06:42 by bchanaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	src_size;
	size_t	dest_size;
	size_t	j;

	j = 0;
	dest_size = 0;
	src_size = ft_strlen(src);
	if (dstsize == 0)
		return (src_size);
	while (dst[dest_size] != '\0')
	{
		if (dest_size >= dstsize)
			return (src_size + dstsize);
		dest_size++;
	}
	while ((dest_size + j) < dstsize - 1 && j < src_size)
	{
		dst[dest_size + j] = src[j];
		j++;
	}
	dst[dest_size + j] = '\0';
	return (src_size + dest_size);
}
