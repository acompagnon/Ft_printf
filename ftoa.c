/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 18:49:25 by acompagn          #+#    #+#             */
/*   Updated: 2018/12/21 17:48:29 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

/*char		*ft_ftoa(double f, int precision)
{
	long long			intpart;
	unsigned long long 	floatpart;
	int					n;

	intpart = (long long)f;
	f = f - (double)intpart;
	if (!precision)
		precision = 6;
	while (precision--)
	{
		f = f * 10;
		if (!precision && f > 0.5)
			f++;
		floatpart = (unsigned long long)f;
		f = f - (double)intpart;
	}
}*/

/*void		binary_float(double f)
{
	unsigned long long a;
	unsigned long long result;
	unsigned long long tab[32];
	int str[32];
	unsigned long long som;
	int i;

	a = (unsigned long long)f;
	som = 1;
	i = 0;
	while (i < 32)
	{
		tab[i++] = som;
		som = som*2;
	}
	i = 0;
	while (i <= 32)
	{
		result = a & tab[i];
		printf("result = %llu\n", result);
		printf("a = %llu\n", a);
		printf("tab[i] = %llu\n", tab[i]);
		if (result == tab[i])
			str[i] = 1;
		else
			str[i] = 0;
		i++;
	}  
	printf("Binary representation: ");
	i = 31;
	while (i >= 0)
		printf("%d", str[i--]);
}*/

void		binary_float(double f, int precision)
{
	float floatpart;
	int l;
	float tmp_f;
	int intpart;
	int tab[20];
	int tmp;
	int i;

	intpart = (int)f;
	floatpart = (double)f - intpart;
	printf("intpart = %d\nfloatpart = %f\n", intpart, floatpart);
	i = 0;
	while (intpart)
	{
		tmp = intpart % 2;
		intpart /= 2;
		tab[i++] = tmp;
	}
	//intpart binaire range a l'envers dans tab;
	if (!precision)
		precision = 6;
	while (precision--)
	{
		floatpart *= 2;
		tmp_f = floatpart;
		printf("%f", tmp_f);
		if(tmp_f == 1)
			floatpart = floatpart - tmp_f;
	}
}

int		main()
{
	binary_float(3.1415, 0);
	return (0);
}
