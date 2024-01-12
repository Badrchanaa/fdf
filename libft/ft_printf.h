/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchanaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 11:52:33 by bchanaa           #+#    #+#             */
/*   Updated: 2023/11/22 20:18:12 by bchanaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# define LJUSTIFY 1
# define BLANK 2
# define MAXWIDTH 4
# define HASH 8
# define ZEROPAD 16
# define ADDSIGN 32
# define FLAGS "0#+- "
# define SPECIFIERS "cspdiuxX%"	
# define HEX_LOWER "0123456789abcdef"
# define HEX_UPPER "0123456789ABCDEF"
# define DECIMAL "0123456789"
# include <stdarg.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>

typedef struct s_flags
{
	int				maxw;
	int				minw;
	unsigned int	flags;
}				t_flags;

t_flags	*t_flags_default(void);
int		ft_printf(const char *s, ...);
void	ft_setflag(unsigned int *curr_flags, char c);
int		print_str(char *s, t_flags *fl, bool should_free, bool check_null);
char	*ft_itoa_base(uintmax_t nbr, char *base);
int		print_hex(unsigned int nb, t_flags *fl, bool is_upper);
int		print_decimal(int nb, t_flags *fl);
int		print_unsigned(unsigned int nb, t_flags *fl);
int		print_addr(uintmax_t addr, t_flags *fl);
int		print_char(char c, t_flags *fl);
char	*format_number(char *num, t_flags *fl, bool should_free);
char	*format_str(char *s, t_flags *fl);
void	handle_flags_conflicts(t_flags *fl, char sp);
char	*prepend_sign(char *buff, t_flags *fl, bool is_negative);
char	*fill_str(char *s, char c, int count, bool jus_left);
char	*add_hex_prefix(char *num_hex, bool should_free, bool is_upper);

#endif
