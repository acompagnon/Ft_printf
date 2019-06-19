/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 13:29:38 by acompagn          #+#    #+#             */
/*   Updated: 2019/02/27 16:38:50 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	abs;

	(n < 0) ? write(fd, "-", 1) : 1;
	abs = (n < 0) ? -n : n;
	if (abs > 9)
		ft_putnbr_fd(abs / 10, fd);
	ft_putchar_fd((abs % 10) + 48, fd);
}
