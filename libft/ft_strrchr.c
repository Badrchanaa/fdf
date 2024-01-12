/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchanaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 15:00:54 by bchanaa           #+#    #+#             */
/*   Updated: 2023/11/07 11:31:23 by bchanaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	cc;

	cc = (char)c;
	i = 0;
	if (cc == 0 && s[0] == 0)
		return ((char *)s);
	while (s[i])
		i++;
	while (i >= 0)
	{
		if (s[i] == cc)
			return ((char *)(s + i));
		i--;
	}
	return (0);
}
