/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 12:05:30 by acompagn          #+#    #+#             */
/*   Updated: 2019/01/04 18:52:39 by acompagn         ###   ########.fr       */
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
	while (lst)
	{
		printf("%d\n", lst->nb);
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
	int		restart;
	t_bint	*curr;

	restart = 1;
	while (restart)
	{
		curr = lst;
		restart = 0;
		while (curr->next)
		{
			if (curr->next->nb > 9)
			{
				curr->nb += 1;
				curr->next->nb -= 10;
				restart = 1;
			}
			curr = curr->next;
		}
	}
}

void		ft_add(t_bint *lst1, t_bint *lst2)
{
	t_bint	*tmp1;
	t_bint	*tmp2;

	tmp1 = lst1;
	tmp2 = lst2;
	while (tmp1)
	{
		tmp2->nb = tmp2->nb + tmp1->nb;
		tmp1 = tmp1->next;
		if (!tmp2->next && tmp1)
			tmp2->next = lst_init(tmp2, 0);
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
	t_bint		*curr;
	char		tmp;
	char		retenue;

	curr = lst;
	retenue = 0;
	while (curr)
	{
		tmp = curr->nb;
		curr->nb = curr->nb / 2 + retenue;
		retenue = (tmp % 2) * 5;
		if (!curr->next && retenue)
			curr->next = lst_init(curr->next, 0);
		curr = curr->next;
	}
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

void		int_aug(int p, t_bint *int_lst, t_bint *float_lst)
{
	t_bint	*curr;

	curr = int_lst;
	if ((curr->nb % 2 != 0 && float_lst->nb == 5 && p != 1) ||
		(float_lst->nb > 9) || (p < 1 && curr->nb % 2 != 0 &&
		float_lst->nb >= 5) || (!p && float_lst->nb >= 5))
	{
		curr->nb += 1;
		float_lst->nb = 0;
	}
	ft_check_ten(int_lst);
}

char		*ft_create_str(int p, t_bint *int_lst, t_bint *float_lst)
{
	int		size;
	int		i;
	int		j;
	t_bint	*intpart;
	char	*keep;

	size = 0;
	intpart = int_lst;
	j = 0;
	while (intpart)
	{
		size++;
		intpart = intpart->next;
	}
	i = size;
	if (!(keep = (char *)malloc(sizeof(char) * (size + (p ? p + 1 : p)))))
		return (NULL);
	while (int_lst)
	{
		keep[--size] = int_lst->nb + 48;
		int_lst = int_lst->next;
	}
	if (p)
		keep[i++] = '.';
	while (j < p)
	{
		keep[i + j++] = float_lst->nb + 48;
		float_lst = float_lst->next;
	}
	return (keep);
}

char		*ft_precision(int p, t_bint *int_lst, t_bint *float_lst)
{
	t_bint	*curr;
	int		len;

	curr = float_lst;
	len = 0;
	while (++len < p)
	{
		if (!curr->next)
			curr->next = lst_init(curr->next, 0);
		curr = curr->next;
	}
	if (p && curr->next)
	{
		if ((curr->next->nb == 5 && (curr->next->next ||
			curr->nb % 2 != 0)) || (curr->next->nb > 5))
			curr->nb += 1;
		ft_check_float(float_lst);
	}
	if (float_lst->nb >= 5 && p <= 1)
		int_aug(p, int_lst, float_lst);
	return (ft_create_str(p, int_lst, float_lst));
}

char		*ftoa(float f, int p)
{
	unsigned char	*tab;
	t_float			*lst;
	int				i;
	int				c;
	char			str[33];

	if (!(lst = (t_float*)malloc(sizeof(t_float))))
		return (0);
	str[32] = 0;
	i = 0;
	c = 4;
	tab = (unsigned char *)&f;
	while (c--)
		print_bits(*(tab + c), str, &i);
	lst->sign = (str[0] == '0') ? 1 : -1;
	ft_get_exp_mant(str, lst);
	ft_get_point(lst);
	return (ft_precision(p, ft_intpart(lst), ft_floatpart(lst)));
}

/*int		main()
{
	float	f;
	int		p;

	f = 2.7530696392059326171875000000000000000000000000000000000000000000000000000000000000000000000000000000;
	p = 0;
	printf("vrai printf: %.0f\n", f);
	printf("mon printf: %s\n", ftoa(f, p));
	return (0);
}*/
