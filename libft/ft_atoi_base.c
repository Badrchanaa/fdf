/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchanaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 21:42:17 by bchanaa           #+#    #+#             */
/*   Updated: 2023/12/20 23:32:51 by bchanaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_skip_to_n(char *str, int *minus_count)
{
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	while (*str == '-' || *str == '+')
	{
		if (*str == '-')
			(*minus_count)++;
		str++;
	}
	return (str);
}

int	get_char_index(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	ft_atoi_base(char *str, const char *base, int base_len)
{
	int	result;
	int	minus_count;
	int	char_value;

	result = 0;
	minus_count = 0;
	str = ft_skip_to_n(str, &minus_count);
	while (*str != '\0')
	{
		char_value = get_char_index(base, *str);
		if (char_value != -1)
			result = (result * base_len) + char_value;
		else
			break ;
		str++;
	}
	if (minus_count % 2 == 1)
		return (result * -1);
	return (result);
}
