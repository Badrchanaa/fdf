/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchanaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 10:39:49 by bchanaa           #+#    #+#             */
/*   Updated: 2023/11/11 13:16:12 by bchanaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	needle_size;
	size_t	i;

	i = 0;
	if (len == 0 && needle && *needle)
		return (0);
	needle_size = ft_strlen(needle);
	if (needle_size == 0)
		return ((char *)haystack);
	while (haystack[i] != '\0' && i + needle_size <= len)
	{
		if (haystack[i] == needle[0])
		{
			if (ft_strncmp(haystack + i, needle, needle_size) == 0)
				return ((char *)haystack + i);
		}
		i++;
	}
	return (0);
}
