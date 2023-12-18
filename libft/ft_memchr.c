/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchanaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:22:38 by bchanaa           #+#    #+#             */
/*   Updated: 2023/11/11 13:09:26 by bchanaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	unsigned char		ucc;
	const unsigned char	*us;

	i = 0;
	us = (const unsigned char *)s;
	ucc = (unsigned char)c;
	while (i < n)
	{
		if (us[i] == ucc)
			return ((void *)(s + i));
		i++;
	}
	return (0);
}
