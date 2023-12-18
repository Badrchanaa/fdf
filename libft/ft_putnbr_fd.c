/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchanaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 11:23:56 by bchanaa           #+#    #+#             */
/*   Updated: 2023/11/08 11:22:37 by bchanaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	nbr;
	char	c[10];
	int		i;

	if (fd < 0)
		return ;
	nbr = n;
	if (nbr < 0)
	{
		write(fd, "-", 1);
		nbr = nbr * -1;
	}
	i = 0;
	while (nbr >= 10)
	{
		c[i] = (nbr % 10) + '0';
		nbr = nbr / 10;
		i++;
	}
	c[i] = nbr + '0';
	while (i >= 0)
	{
		write(fd, &c[i], 1);
		i--;
	}
}
