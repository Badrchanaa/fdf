/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchanaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 19:20:38 by bchanaa           #+#    #+#             */
/*   Updated: 2023/11/06 18:06:01 by bchanaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*buff;
	size_t			i;

	i = 0;
	if (size > 0 && count > SIZE_MAX / size)
		return (NULL);
	buff = (unsigned char *)malloc(sizeof(unsigned char) * count * size);
	if (!buff)
		return (NULL);
	while (i < count * size)
	{
		buff[i] = 0;
		i++;
	}
	return (buff);
}
