/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchanaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 21:15:28 by bchanaa           #+#    #+#             */
/*   Updated: 2023/12/15 17:17:30 by bchanaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

int	print_str(char *s, t_flags *fl, bool should_free, bool check_null)
{
	char	*buff;
	int		print_len;

	if (check_null && !s)
		return (-1);
	buff = format_str(s, fl);
	if (should_free)
		free(s);
	if (!buff)
		return (-1);
	print_len = write(1, buff, ft_strlen(buff));
	free(buff);
	return (print_len);
}

int	print_unsigned(unsigned int nb, t_flags *fl)
{
	char	*converted;
	char	*tmp;

	if (nb == 0 && fl->maxw == 0 && fl->minw >= 0)
		tmp = ft_strdup("");
	else
		tmp = ft_itoa_base(nb, DECIMAL);
	if (!tmp)
		return (-1);
	converted = format_number(tmp, fl, true);
	if (!converted)
		return (-1);
	return (print_str(converted, fl, 1, 1));
}

int	print_decimal(int nb, t_flags *fl)
{
	char			*tmp;
	char			*buff;
	unsigned int	unb;

	unb = nb;
	if (nb < 0)
		unb = -nb;
	if ((nb < 0 || fl->flags & (ADDSIGN | BLANK)) && fl->minw < 0)
		fl->maxw--;
	if (nb == 0 && fl->maxw == 0 && fl->minw >= 0)
		tmp = ft_strdup("");
	else
		tmp = ft_itoa_base(unb, DECIMAL);
	if (!tmp)
		return (-1);
	buff = format_number(tmp, fl, true);
	if (!buff)
		return (-1);
	tmp = prepend_sign(buff, fl, nb < 0);
	if (!tmp)
		return (-1);
	return (print_str(tmp, fl, 1, 1));
}

int	print_hex(unsigned int nb, t_flags *fl, bool is_upper)
{
	char	*tmp;
	char	*converted;

	if (nb == 0 && fl->maxw == 0 & fl->minw >= 0)
		tmp = ft_strdup("");
	else if (is_upper)
		tmp = ft_itoa_base(nb, HEX_UPPER);
	else
		tmp = ft_itoa_base(nb, HEX_LOWER);
	if (!tmp)
		return (-1);
	if (fl->flags & HASH && fl->minw < 0 && !nb)
		fl->maxw += 2;
	converted = format_number(tmp, fl, true);
	if (!converted)
		return (-1);
	tmp = converted;
	if ((fl->flags & HASH) && nb)
		tmp = add_hex_prefix(converted, true, is_upper);
	return (print_str(tmp, fl, 1, 1));
}

int	print_addr(uintmax_t addr, t_flags *fl)
{
	char	*tmp;
	char	*converted;

	tmp = ft_itoa_base(addr, HEX_LOWER);
	if (!tmp)
		return (-1);
	converted = ft_strjoin("0x", tmp);
	free(tmp);
	if (!converted)
		return (-1);
	return (print_str(converted, fl, 1, 1));
}
