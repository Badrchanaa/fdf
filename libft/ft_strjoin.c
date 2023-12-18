/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchanaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 12:13:30 by bchanaa           #+#    #+#             */
/*   Updated: 2023/11/06 10:51:41 by bchanaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_joinsize(char const *s1, char const *s2)
{
	size_t	s1len;
	size_t	s2len;

	s1len = 0;
	s2len = 0;
	if (s1)
		s1len = ft_strlen(s1);
	if (s2)
		s2len = ft_strlen(s2);
	return (s1len + s2len);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	size_t	res_len;

	if (!s1 && !s2)
		return (NULL);
	res_len = ft_count_joinsize(s1, s2) + 1;
	res = ft_calloc(res_len, sizeof(char));
	if (!res)
		return (NULL);
	if (s1)
		ft_strlcat(res, s1, res_len);
	if (s2)
		ft_strlcat(res, s2, res_len);
	return (res);
}
