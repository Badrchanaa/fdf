/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchanaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:37:34 by bchanaa           #+#    #+#             */
/*   Updated: 2023/11/07 11:25:41 by bchanaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in_str(char c, const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	count_trim(char *s1, char *set, int *s_trim, int *e_trim)
{
	int				i;
	int				slen;

	i = 0;
	slen = (int) ft_strlen(s1);
	while (i < slen)
	{
		if (!is_in_str(s1[i], set))
		{
			*s_trim = i;
			break ;
		}
		i++;
	}
	i = slen - 1;
	while (i >= 0)
	{
		if (!is_in_str(s1[i], set))
		{
			*e_trim = i + 1;
			break ;
		}
		i--;
	}
	return (slen);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	int		s_trim;
	int		e_trim;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	s_trim = -1;
	e_trim = -1;
	count_trim((char *)s1, (char *)set, &s_trim, &e_trim);
	if (s_trim == -1 || e_trim == -1)
		res = ft_substr("", 0, 0);
	else
		res = ft_substr(s1, s_trim, e_trim - s_trim);
	return (res);
}
