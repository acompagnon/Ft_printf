/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 12:05:30 by acompagn          #+#    #+#             */
/*   Updated: 2018/12/30 19:01:11 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct		s_float
{
	char			mant[25];
	char			*binary;
	char			*keep;
	int				sign;
	int				intexp;
	int				intpart;
	long long		fpart;
}					t_float;

typedef struct		s_bint
{
	char			nb;
	struct s_bint	*next;
}					t_bint;

t_bint		*lst_init(t_bint *lst, char nb)
{
	if (!(lst = (t_bint *)malloc(sizeof(t_bint))))
		return (NULL);
	lst->nb = nb;
	lst->next = NULL;
	return (lst);
}

void		print_lst(t_bint *lst)
{
	printf("Print_lst:\n");
	while (lst)
	{
		printf("%d", lst->nb);
		lst = lst->next;
	}
	printf("\n");
}

void		ft_check_ten(t_bint *lst)
{
	t_bint	*curr;
	
	curr = lst;
	while (curr)
	{
		if (curr->nb > 9)
		{
			if (!curr->next)
				curr->next = lst_init(curr->next, 0);
			curr->nb -= 10;
			curr = curr->next;
			curr->nb += 1;
		}
		else
			curr = curr->next;
	}
}

void		ft_check_float(t_bint *lst)
{
	printf("CHECK FLOAT\n");
	t_bint	*curr;

	curr = lst;
	while (curr->next)
	{
		if (curr->next->nb > 9)
		{
			curr->nb += 1;
			curr->next->nb -= 10;
		}
		curr = curr->next;
	}
}

void		ft_add(t_bint *lst1, t_bint *lst2)
{
	t_bint	*tmp1;
	t_bint	*tmp2;
	
	tmp1 = lst1;
	tmp2 = lst2;
	while (tmp1 && tmp2)
	{
		tmp2->nb = tmp2->nb + tmp1->nb;
		tmp1 = tmp1->next;
		tmp2 = tmp2->next;
	}
}

void		ft_double(t_bint *lst1)
{
	t_bint	*tmp;
	
	tmp = lst1;
	while (tmp)
	{
		tmp->nb *= 2;
		tmp = tmp->next;
	}
	ft_check_ten(lst1);
}

t_bint		*ft_intpart(t_float *lst)
{
	int		i;
	t_bint	*lst1;
	t_bint	*lst2;

	i = 0;
	lst1 = lst_init(lst1, 1);
	lst2 = lst_init(lst2, 0);
	while (lst->binary[i + 1] != '.')
		i++;
	while (i >= 0)
	{
		if (lst->binary[i] == '1')
		{
			ft_add(lst1, lst2);
			ft_check_ten(lst2);
		}
		ft_double(lst1);
		i--;
	}
	return (lst2);
}

void		ft_multiply(t_bint *lst)
{
	printf("MULT\n");
	t_bint		*curr;
	char		tmp;
	char		retenue;

	curr = lst;
	retenue = 0;
	printf("avant mult =\n");
	print_lst(lst);
	while (curr)
	{
		tmp = curr->nb;
		curr->nb = curr->nb / 2 + retenue;
		retenue = (tmp % 2) * 5;
		printf("retenue = %d\n", retenue);
		if (!curr->next && retenue)
			curr->next = lst_init(curr->next, 0);
		curr = curr->next;
	}
	printf("apres mult = \n");
	print_lst(lst);
}

t_bint		*ft_floatpart(t_float *lst)
{
	t_bint		*lst1;
	t_bint		*lst2;
	int			i;

	i = 0;
	lst1 = lst_init(lst1, 5);
	lst2 = lst_init(lst2, 0);
	while (lst->binary[i] != '.')
		i++;
	if (!(lst->binary[i + 1]))
		return (0);
	i++;
	while (lst->binary[i])
	{
		if (lst->binary[i] == '1')
		{
			ft_add(lst1, lst2);
			ft_check_float(lst2);
		}
		ft_multiply(lst1);
		i++;
	}
	return (lst2);
}

void		final_string(t_float *lst, int *tab_int, int *tab_float, int precision)
{
	int		size;
	int		i;
	int		j;

	size = ft_strlen(lst->binary) / 3 + ft_strlen(lst->binary) % 3;
	i = 0;
	j = 0;
	if (!(lst->keep = (char *)malloc(sizeof(char) * (size * 2 + 1))))
		return ;
	while (tab_int[i] == 0 && i < size + 10)
		i++;
	if (lst->sign == -1)
		lst->keep[j++] = '-';
	while (i <= size)
		lst->keep[j++] = tab_int[i++] + 48;
	lst->keep[j++] = '.';
	i = 0;
	while (i < precision - 1)
		lst->keep[j++] = tab_float[i++] + 48;
	if (tab_float[i + 1] > 5)
		lst->keep[j++] = (tab_float[i] + 1) + 48;
	else
		lst->keep[j++] = tab_float[i] + 48;
	lst->keep[j] = '\0';
	printf("keep = %s\n", lst->keep);
}

int			main()
{
	unsigned char	*tab;
	float			f;
	t_float			*lst;
	int				i;
	int				c;
	int				precision;
	char			str[33];

	if (!(lst = (t_float*)malloc(sizeof(t_float))))
		return (0);
	str[32] = 0;
	i = 0;
	c = 4;
	f = 1.25;
	precision = 10;
	tab = (unsigned char *)&f;
	while (c--)
		print_bits(*(tab + c), str, &i);
	lst->sign = (str[0] == '0') ? 1 : -1;
	ft_get_exp_mant(str, lst);
	printf("mantisse = %s\n", lst->mant);
	ft_get_point(lst);
	printf("vrai printf: %.10f\n", f);
	print_lst(ft_intpart(lst));
	print_lst(ft_floatpart(lst));
	//final_string(lst, ft_intpart(lst), ft_floatpart(lst), precision);
	return (0);
}
