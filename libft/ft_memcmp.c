/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchanaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:56:02 by bchanaa           #+#    #+#             */
/*   Updated: 2023/10/31 20:32:01 by bchanaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	tmp1;
	unsigned char	tmp2;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n)
	{
		tmp1 = ((unsigned char *)s1)[i];
		tmp2 = ((unsigned char *)s2)[i];
		if (tmp1 != tmp2)
			return (tmp1 - tmp2);
		i++;
	}
	return (0);
}
