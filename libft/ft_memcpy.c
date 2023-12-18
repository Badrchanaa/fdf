/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchanaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 19:46:10 by bchanaa           #+#    #+#             */
/*   Updated: 2023/11/03 10:49:15 by bchanaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*idst;
	unsigned char	*isrc;

	idst = (unsigned char *)dst;
	isrc = (unsigned char *)src;
	if (!dst && !src)
		return (dst);
	i = 0;
	while (i < n)
	{
		idst[i] = isrc[i];
		i++;
	}
	return (dst);
}
