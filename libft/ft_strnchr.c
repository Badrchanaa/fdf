/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchanaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:06:46 by bchanaa           #+#    #+#             */
/*   Updated: 2023/12/15 17:38:35 by bchanaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnchr(const char *s, int c, size_t n)
{
	size_t	i;
	char	cc;

	if (!s)
		return (0);
	cc = (char) c;
	i = 0;
	while (i < n)
	{
		if (s[i] == cc)
			return ((char *)(s + i));
		i++;
	}
	return (0);
}
