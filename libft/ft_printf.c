/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchanaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 11:34:17 by bchanaa           #+#    #+#             */
/*   Updated: 2023/12/15 17:17:02 by bchanaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

int	ft_atoi_skip(const char *s, int *res)
{
	int	i;

	i = 0;
	*res = ft_atoi(s);
	while (s[i] && ft_isdigit(s[i]))
		i++;
	return (i);
}

void	ft_handle_print(char sp, t_flags *fl, va_list *ap, int *count)
{
	int	plen;

	plen = 0;
	handle_flags_conflicts(fl, sp);
	if (sp == 'c')
		plen = print_char((char)va_arg(*ap, int), fl);
	else if (sp == '%')
		plen = print_char('%', fl);
	else if (sp == 's')
		plen = print_str(va_arg(*ap, char *), fl, 0, 0);
	else if (sp == 'd' || sp == 'i')
		plen = print_decimal(va_arg(*ap, int), fl);
	else if (sp == 'u')
		plen = print_unsigned(va_arg(*ap, unsigned int), fl);
	else if (sp == 'p')
		plen = print_addr((uintmax_t)va_arg(*ap, void *), fl);
	else if (sp == 'x' || sp == 'X')
		plen = print_hex(va_arg(*ap, unsigned int), fl, sp == 'X');
	if (plen == -1)
		*count = -1;
	else
		*count += plen;
}

int	ft_print_conversion(const char *s, int *count, va_list *ap)
{
	int		j;
	t_flags	*fl;

	fl = t_flags_default();
	if (!fl)
		return (-1);
	j = 1;
	while (ft_strchr(FLAGS, s[j]))
		ft_setflag(&(fl->flags), s[j++]);
	if (ft_isdigit(s[j]))
		j += ft_atoi_skip(s + j, &(fl->minw));
	if (s[j] == '.')
	{
		ft_setflag(&(fl->flags), '.');
		j += ft_atoi_skip(s + j + 1, &(fl->maxw)) + 1;
	}
	if (ft_strchr(SPECIFIERS, s[j]))
		ft_handle_print(s[j++], fl, ap, count);
	free(fl);
	return (j);
}

int	ft_printf(const char *s, ...)
{
	va_list	ap;
	int		i;
	int		count;
	int		j;

	va_start(ap, s);
	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '%')
		{
			j = ft_print_conversion(s + i, &count, &ap);
			if (count == -1 || j == -1)
				return (-1);
			i += j;
			continue ;
		}
		if (write(1, s + i, 1) < 0)
			return (-1);
		count++;
		i++;
	}
	va_end(ap);
	return (count);
}
