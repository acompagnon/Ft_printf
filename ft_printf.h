/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 21:48:26 by acompagn          #+#    #+#             */
/*   Updated: 2018/12/17 16:36:28 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# define BUFFER_SIZE 1000
# include <stdio.h>
# include <stdarg.h>
# include <unistd.h>
# include "libft.h"

typedef struct		s_print
{
	char			buf[BUFFER_SIZE + 1];
	int				i;
	int				a;
}					t_print;

typedef struct		s_flags
{
	int				minus;
	int				plus;
	int				hashtag;
	int				zero;
	int				space;
	int				width;
	int				precision;
}					t_flags;

char				*ft_itoa_base(uintmax_t a, char *base);
char				*ft_decimal_itoa(intmax_t nb);
char				*ft_octal(uintmax_t a, char *keep);
char				*ft_hexadecimal(intmax_t a, const char *format);
char				*ft_itoa_addr(uintmax_t a);
char				*ft_pointer(va_list ap);
char				*ft_char(va_list ap, t_print *lst);
char				*ft_string(va_list ap);
char				*ft_unsigned(uintmax_t a);
const char			*ft_get_lh(const char *format, int *h, int *l);
intmax_t			ft_get_signed(va_list ap, int h, int l);
uintmax_t			ft_get_unsigned(va_list ap, int h, int l);

#endif
