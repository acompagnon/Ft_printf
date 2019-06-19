/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_words_tables.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 14:30:31 by acompagn          #+#    #+#             */
/*   Updated: 2019/02/27 16:00:07 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_words_tables(char **tab)
{
	int i;
	int j;
	int size;

	i = -1;
	size = 0;
	while (tab[size] != 0)
		size++;
	while (++i < size)
	{
		j = -1;
		while (tab[i][++j])
			write(1, &tab[i][j], 1);
		write(1, "\n", 1);
	}
}
