/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchanaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 19:10:48 by bchanaa           #+#    #+#             */
/*   Updated: 2023/11/16 17:24:02 by bchanaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char f(unsigned int, char))
{
	size_t	len;
	char	*ms;
	size_t	i;

	if (!f || !s)
		return (NULL);
	i = 0;
	len = ft_strlen(s);
	ms = (char *)malloc(sizeof(char) * (len + 1));
	if (!ms)
		return (NULL);
	while (i < len)
	{
		ms[i] = f(i, s[i]);
		i++;
	}
	ms[i] = '\0';
	return (ms);
}
