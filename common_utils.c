/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchanaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 16:19:32 by bchanaa           #+#    #+#             */
/*   Updated: 2024/01/19 20:37:26 by bchanaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	count_split(char *str, char c)
{
	int		is_empty;
	int		count;

	count = 0;
	is_empty = 1;
	while (*str)
	{
		if (*str == c && !is_empty)
		{
			count++;
			is_empty = 1;
		}
		if (*str != c && is_empty)
			is_empty = 0;
		str++;
	}
	if (!is_empty)
		count++;
	return (count);
}

void	free_2darray(void **arr, bool free_root_p)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	if (free_root_p)
		free(arr);
}

void	exit_wmsg(const char *msg)
{
	ft_printf(msg);
	exit(0);
}

int	abs(int a)
{
	if (a >= 0)
		return (a);
	return (-a);
}