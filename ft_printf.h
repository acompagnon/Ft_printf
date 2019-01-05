/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 21:48:26 by acompagn          #+#    #+#             */
/*   Updated: 2019/01/05 18:13:16 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# define BUFFER_SIZE 1000
# include <stdio.h>
# include <stdarg.h>
# include <unistd.h>
# include "libft.h"
# include <stdlib.h>

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

typedef struct		s_float
{
	char			mant[65];
	char			*keep;
	int				sign;
	unsigned int	intexp;
	int				size;
}					t_float;

typedef struct		s_bint
{
	char			nb;
	struct s_bint	*next;
}					t_bint;

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


char				*ftoa(double f, int p);
char				*lftoa(long double f, int p);
void				print_bits(unsigned char *c, t_float *lst);
t_bint				*lst_init(t_bint *lst, char nb);
void				print_lst(t_bint *lst);
void				ft_check_ten(t_bint *lst);
void				ft_check_float(t_bint *lst);
void				ft_add(t_bint *lst1, t_bint *lst2);
void				ft_double(t_bint *lst1);
t_bint				*ft_intpart(t_float *lst);
void				ft_multiply(t_bint *lst);
t_bint				*ft_floatpart(t_float *lst);
void				int_aug(int p, t_bint *int_lst, t_bint *float_lst);
char				*ft_create_str(int p, t_bint *int_lst, t_bint *float_lst, int sign);
char				*ft_precision(int p, t_bint *int_lst, t_bint *float_lst, int sign);
int					check_double(double f, t_float *lst);
void				print_long(unsigned char *c, t_float *lst);

#endif
