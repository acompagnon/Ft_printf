/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 17:42:25 by acompagn          #+#    #+#             */
/*   Updated: 2019/02/27 16:18:07 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strstr(const char *haystack, const char *needle)
{
	int i;
	int c;
	int size;

	i = 0;
	size = 0;
	while (needle[size] != '\0')
		size++;
	if (!size)
		return ((char *)haystack);
	while (haystack[i] != '\0')
	{
		c = 0;
		while (haystack[i + c] == needle[c])
		{
			c++;
			if (c == size)
				return ((char *)&haystack[i]);
		}
		i++;
	}
	return (0);
}
