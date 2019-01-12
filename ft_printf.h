/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 21:48:26 by acompagn          #+#    #+#             */
/*   Updated: 2019/01/12 20:26:09 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# define BUFFER_SIZE 1000
# define FORMAT_DOU (**format == 'D' || **format == 'O' || **format == 'U')
# include <stdio.h>
# include <stdarg.h>
# include <unistd.h>
# include "libft.h"
# include <stdlib.h>

typedef struct			s_print
{
	char				buf[BUFFER_SIZE + 1];
	int					i;
	int					a;
	char				*keep;
}						t_print;

typedef struct			s_flags
{
	int					minus;
	int					plus;
	int					hashtag;
	int					zero;
	int					space;
	int					width;
	int					precision;
	int					h;
	int					l;
	int					llf;
	int					z;
	int					j;
	int					star;
}						t_flags;

typedef struct			s_float
{
	char				mant[65];
	char				*keep;
	int					sign;
	unsigned int		intexp;
	int					size;
}						t_float;

typedef struct			s_bint
{
	char				nb;
	struct s_bint		*next;
}						t_bint;

typedef struct			s_itoa
{
	int					len;
	unsigned long long	nb;
	intmax_t			nbr;
	int					size;
	int					zero_case;
	char				keep[21];
	int					keep_len;
}						t_itoa;

void					ft_empty_buf(t_print *lst);
void					ft_init_lst(t_flags *flags);
void					print_lst_init(t_print *lst);
void					lst_itoa_init(t_itoa *list);
char					*get_nb(va_list ap, char *str, t_flags *flags);
int						get_wildcard(va_list ap, t_flags *flags, int ok);
int						ft_get_type(char *format, va_list ap, t_print *lst,
						t_flags *flags);
void					ft_put_in_buf(char *keep, t_print *lst, t_flags *flags);
void					ft_itoa_base(uintmax_t a, char *base, t_print *lst,
						t_flags *flags);
void					ft_itoa_dec(intmax_t nb, t_print *lst, t_flags *flags);
void					ft_octal(uintmax_t a, t_print *lst, t_flags *flags);
void					ft_hexadecimal(intmax_t a, char c, t_print *lst,
						t_flags *flags);
void					ft_itoa_addr(uintmax_t a, t_print *lst, t_flags *flags);
void					ft_pointer(va_list ap, t_print *lst, t_flags *flags);
void					ft_char(va_list ap, t_print *lst, t_flags *flags);
void					apply_width(t_print *lst, t_flags *flags, int len);
void					string_width(t_print *lst, t_flags *flags, int len);
void					ft_string(char *s, t_print *lst, t_flags *flags);
void					ft_percent(t_print *lst, t_flags *flags, char format);
void					ft_unsigned(uintmax_t a, t_print *lst, t_flags *flags);
intmax_t				ft_get_signed(va_list ap, t_flags *flags);
uintmax_t				ft_get_unsigned(va_list ap, t_flags *flags);

void					float_call(va_list ap, t_print *lst, t_flags *flags,
						char format);
void					print_bits(unsigned char *c, t_float *lst);
t_bint					*lst_init(t_bint *lst, char nb);
void					ft_check_ten(t_bint *lst);
void					ft_check_float(t_bint *lst);
t_bint					*ft_intpart(t_float *lst);
t_bint					*ft_floatpart(t_float *lst);
char					*ft_precision(int p, t_bint *int_lst, t_bint *float_lst,
						int sign);
int						check_double(double f, t_float *lst);
int						check_long_double(long double f, t_float *lst);
void					print_long(unsigned char *c, t_float *lst);
void					free_lst(t_bint *begin_lst);
void					ft_add(t_bint *lst1, t_bint *lst2);
void					ft_multiply(t_bint *lst);
t_bint					*free_time(t_float *lst_float, t_bint *lst_bint);
char					*malloc_fail(t_bint *int_lst, t_bint *float_lst);
int						check_validity(t_bint *int_lst, t_bint *float_lst);

char					*ftoa(double f, int p);
char					*lftoa(long double f, int p);
#endif
