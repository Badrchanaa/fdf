/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchanaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 20:17:27 by bchanaa           #+#    #+#             */
/*   Updated: 2023/12/15 17:19:10 by bchanaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

char	*add_hex_prefix(char *num, bool should_free, bool is_upper)
{
	char	*prefix;
	char	*res;

	if (is_upper)
		prefix = "0X";
	else
		prefix = "0x";
	res = ft_strjoin(prefix, num);
	if (should_free)
		free(num);
	return (res);
}

char	*prepend_sign(char *buff, t_flags *fl, bool is_negative)
{
	char	*res;
	bool	should_decrement;

	should_decrement = true;
	if (is_negative)
		res = ft_strjoin("-", buff);
	else if (fl->flags & ADDSIGN)
		res = ft_strjoin("+", buff);
	else if (fl->flags & BLANK)
		res = ft_strjoin(" ", buff);
	else
	{
		res = ft_strdup(buff);
		should_decrement = false;
	}
	free(buff);
	if (!res)
		return (NULL);
	if (should_decrement && fl->flags & ZEROPAD)
		fl->minw--;
	return (res);
}

t_flags	*t_flags_default(void)
{
	t_flags	*fl;

	fl = malloc(sizeof(t_flags));
	if (!fl)
		return (NULL);
	fl->maxw = -1;
	fl->minw = 0;
	fl->flags = 0;
	return (fl);
}

void	handle_flags_conflicts(t_flags *fl, char sp)
{
	if (sp == '%' && fl->flags & LJUSTIFY)
		fl->flags &= ~(ZEROPAD);
	if (fl->flags & ADDSIGN && fl->flags & BLANK)
		fl->flags ^= BLANK;
	if (ft_strchr("diuxX", sp))
	{
		if (fl->maxw != -1)
			fl->flags &= ~(ZEROPAD);
		else if (fl->minw > 0 && fl->flags & ZEROPAD)
		{
			fl->flags &= ~(ZEROPAD);
			fl->maxw = fl->minw;
			fl->minw = -1;
			if (fl->flags & HASH)
				fl->maxw -= 2;
		}
	}
}

void	ft_setflag(unsigned int *curr_flags, char c)
{
	if (c == '.')
		*curr_flags |= MAXWIDTH;
	else if (c == '0')
		*curr_flags |= ZEROPAD;
	else if (c == '#')
		*curr_flags |= HASH;
	else if (c == '+')
		*curr_flags |= ADDSIGN;
	else if (c == '-')
		*curr_flags |= LJUSTIFY;
	else if (c == ' ')
		*curr_flags |= BLANK;
}
