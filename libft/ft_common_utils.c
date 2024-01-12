/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_common_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchanaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 21:10:23 by bchanaa           #+#    #+#             */
/*   Updated: 2023/12/15 17:17:52 by bchanaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

char	*fill_str(char *s, char c, int count, bool jus_left)
{
	char	*tmp;
	char	*res;

	if (count <= 0)
		return (ft_strdup(s));
	tmp = ft_calloc(sizeof(char), count + 1);
	if (!tmp)
		return (NULL);
	ft_memset(tmp, c, count);
	if (jus_left)
		res = ft_strjoin(s, tmp);
	else
		res = ft_strjoin(tmp, s);
	free(tmp);
	return (res);
}

char	*ft_itoa_base(uintmax_t nbr, char *base)
{
	char	*converted;
	char	digits[32];
	int		i;
	int		j;
	size_t	base_len;

	base_len = ft_strlen(base);
	i = 0;
	while (nbr >= base_len)
	{
		digits[i++] = base[nbr % base_len];
		nbr = nbr / base_len;
	}
	digits[i] = base[nbr];
	converted = (char *)malloc(sizeof(char) * (i + 2));
	if (!converted)
		return (NULL);
	j = 0;
	while (i >= 0)
		converted[j++] = digits[i--];
	converted[j] = '\0';
	return (converted);
}

char	*format_number(char *num, t_flags *fl, bool should_free)
{
	int		num_len;
	char	*res;

	if (!num)
		return (NULL);
	num_len = ft_strlen(num);
	if (fl->maxw > num_len)
		res = fill_str(num, '0', fl->maxw - num_len, 0);
	else
		res = ft_strdup(num);
	fl->maxw = -1;
	if (should_free)
		free(num);
	return (res);
}

char	*format_str(char *s, t_flags *fl)
{
	char	*buff;
	int		buff_len;
	char	c;

	c = 32;
	if (!s)
		buff = ft_strdup("(null)");
	else
		buff = ft_strdup(s);
	if (!buff)
		return (NULL);
	buff_len = ft_strlen(buff);
	if (fl->maxw >= 0 && fl->maxw < buff_len)
	{
		buff_len = fl->maxw;
		buff[buff_len] = 0;
	}
	if (fl->flags & ZEROPAD)
		c = 48;
	s = fill_str(buff, c, fl->minw - buff_len, fl->flags & LJUSTIFY);
	free(buff);
	return (s);
}

int	print_char(char c, t_flags *fl)
{
	char	*buff;
	int		count;
	int		wlen;

	wlen = 0;
	count = 0;
	if (fl->minw <= 1)
		return (write(1, &c, 1));
	buff = fill_str("", 32 + (fl->flags & ZEROPAD), fl->minw - 1, 0);
	if (!buff)
		return (-1);
	if (fl->flags & LJUSTIFY)
		wlen = write(1, &c, 1);
	if (wlen != -1)
		count = write(1, buff, ft_strlen(buff));
	if (!(fl->flags & LJUSTIFY) && count != -1)
		wlen = write(1, &c, 1);
	free(buff);
	if (count < 0 || wlen < 0)
		return (-1);
	return (count + 1);
}
