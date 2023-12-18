/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchanaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 12:52:37 by bchanaa           #+#    #+#             */
/*   Updated: 2023/11/05 15:32:01 by bchanaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strdup_len(char *src, int len)
{
	char	*cpy;
	int		i;

	cpy = (char *)malloc(sizeof(char) * (len + 1));
	if (!cpy)
		return (NULL);
	i = 0;
	while (i < len)
	{
		cpy[i] = src[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

static char	**alloc_array(char *str, char c)
{
	char	**arr;
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
	arr = (char **)malloc(sizeof(char *) * (count + 1));
	if (!arr)
		return (NULL);
	arr[count] = NULL;
	return (arr);
}

static int	ft_free_strs(char **arr, int j)
{
	int	i;

	i = j - 1;
	while (i >= 0)
	{
		free(arr[i]);
		i--;
	}
	free(arr);
	return (-1);
}

static int	ft_split_helper(char **arr, char *str, char c, int *i)
{
	int	j;
	int	start_i;

	start_i = -1;
	j = 0;
	while (str[*i])
	{
		if (str[*i] != c && start_i == -1)
			start_i = *i;
		else if (str[*i] == c && start_i != -1)
		{
			arr[j++] = ft_strdup_len(str + start_i, *i - start_i);
			if (!arr[j - 1])
				return (ft_free_strs(arr, j - 1));
			start_i = -1;
		}
		(*i)++;
	}
	if (start_i != -1)
	{
		arr[j++] = ft_strdup_len(str + start_i, *i - start_i);
		if (!arr[j - 1])
			return (ft_free_strs(arr, j - 1));
	}
	return (j);
}

char	**ft_split(char *str, char c)
{
	char	**arr;
	int		i;
	int		start_i;
	int		j;

	i = 0;
	start_i = 0;
	if (!str)
		return (NULL);
	arr = alloc_array(str, c);
	if (!arr)
		return (NULL);
	j = ft_split_helper(arr, str, c, &i);
	if (j == -1)
		return (NULL);
	return (arr);
}
