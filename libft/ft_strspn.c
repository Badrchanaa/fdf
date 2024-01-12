/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strspn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchanaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 16:50:40 by bchanaa           #+#    #+#             */
/*   Updated: 2023/12/20 17:01:27 by bchanaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strspn(const char *s, const char *charset)
{
	int	i;

	i = 0;
	while (s[i] && ft_strchr(charset, s[i]))
		i++;
	return (i);
}
