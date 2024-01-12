/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchanaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 11:42:45 by bchanaa           #+#    #+#             */
/*   Updated: 2023/11/02 10:52:01 by bchanaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	src_len;

	i = 0;
	src_len = 0;
	while (src[src_len] != '\0')
	{
		src_len++;
	}
	if (dstsize == 0)
		return (src_len);
	while (i < dstsize - 1 && src[i] != '\0')
	{
		if (i < dstsize - 1)
		{
			dst[i] = src[i];
		}
		i++;
	}
	dst[i] = '\0';
	return (src_len);
}
