/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 15:46:26 by acompagn          #+#    #+#             */
/*   Updated: 2019/02/27 15:48:36 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_gnl	*ft_lst(int fd, t_gnl *lst)
{
	t_gnl	*new;

	if (!(new = (t_gnl *)malloc(sizeof(t_gnl))))
		return (NULL);
	new->fd = fd;
	if (!(new->s = ft_strnew(1)))
		return (NULL);
	new->next = NULL;
	new->head = (lst ? lst->head : new);
	if (lst)
		lst->next = new;
	return (new);
}

static t_gnl	*ft_check_fd(t_gnl *lst, int fd)
{
	if (!(lst))
		if (!(lst = ft_lst(fd, lst)))
			return (NULL);
	lst = lst->head;
	while (lst)
	{
		if (lst->fd == fd)
			return (lst);
		if (lst->next == NULL)
		{
			if (!(lst = ft_lst(fd, lst)))
				return (NULL);
			return (lst);
		}
		lst = lst->next;
	}
	return (lst);
}

static int		ft_check_line(char **line, t_gnl *lst)
{
	size_t		i;
	char		*tmp;

	i = 0;
	while (lst->s[i] != '\n' && lst->s[i])
		i++;
	if (!(*line = ft_strsub(lst->s, 0, i)))
		return (-1);
	if (i < ft_strlen(lst->s))
	{
		if (!(tmp = ft_strdup(ft_strchr(lst->s, '\n') + 1)))
			return (-1);
		free(lst->s);
		lst->s = tmp;
	}
	else
		ft_strclr(lst->s);
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	static t_gnl	*lst;
	char			*tmp;
	int				ret;
	char			keep[BUFF_SIZE + 1];

	ret = 0;
	if (fd < 0 || !line || read(fd, keep, 0) == -1 || BUFF_SIZE <= 0)
		return (-1);
	if (!(lst = ft_check_fd(lst, fd)))
		return (-1);
	while (!ft_strchr(lst->s, '\n') && (ret = read(fd, keep, BUFF_SIZE)) > 0)
	{
		keep[ret] = '\0';
		tmp = lst->s;
		if (!(lst->s = ft_strjoin(lst->s, keep)))
			return (-1);
		free(tmp);
	}
	if (ret < BUFF_SIZE && !ft_strlen(lst->s))
		return (0);
	return (ft_check_line(line, lst));
}
