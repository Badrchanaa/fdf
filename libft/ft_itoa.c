/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchanaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:40:19 by bchanaa           #+#    #+#             */
/*   Updated: 2023/11/03 12:37:32 by bchanaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_number(unsigned int n)
{
	int	len;

	len = 1;
	while (n >= 10)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static void	itoa_helper(char *res, int len, unsigned int un, int is_ng)
{
	int	i;

	i = len + is_ng;
	res[len + is_ng] = '\0';
	while (i > 0)
	{
		res[i - 1] = (un % 10) + 48;
		un = un / 10;
		i--;
	}
	if (is_ng)
		res[i] = '-';
}

char	*ft_itoa(int n)
{
	int				len;
	char			*res;
	int				is_ng;
	unsigned int	un;

	is_ng = 0;
	if (n < 0)
	{
		is_ng = 1;
		un = -n;
	}
	else
		un = n;
	len = count_number(un);
	res = (char *)malloc(sizeof(char) * (len + 1 + is_ng));
	if (!res)
		return (NULL);
	itoa_helper(res, len, un, is_ng);
	return (res);
}
