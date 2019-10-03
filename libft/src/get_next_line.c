/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 15:35:30 by mguerrea          #+#    #+#             */
/*   Updated: 2019/09/30 12:30:45 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*char	*ft_save(char *str, char *perm)
{
	if (perm && ft_strchr(perm, '\n'))
		return (ft_strjoin(ft_strchr(perm, '\n') + 1, str));
	if (ft_strchr(str, '\n'))
	{
		free(perm);
		return (ft_strdup(ft_strchr(str, '\n') + 1));
	}
	return (ft_strnew(0));
}

char	*ft_cpy_line(char *dst, char *src, char **perm)
{
	size_t i;
	size_t len;

	i = 0;
	if (*perm && ft_strchr(*perm, '\n'))
	{
		while ((*perm)[i] != '\n')
			i++;
		dst = ft_strncpy(ft_strnew(i), *perm, i);
		*perm = ft_save(src, *perm);
		return (dst);
	}
	while (src[i] != '\n' && src[i])
		i++;
	len = (*perm) ? i + ft_strlen(*perm) : i;
	dst = ft_strnew(len);
	if (*perm)
		dst = ft_strcpy(dst, *perm);
	dst = ft_strncat(dst, src, i);
	*perm = ft_save(src, *perm);
	free(src);
	return (dst);
}

int		get_next_line(int fd, char **line)
{
	int			ret;
	char		buf[BUFF_SIZE + 1];
	t_list		*list;
	static char	*perm[MAX_FD];

	if (!line)
		return (ERROR);
	list = NULL;
	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		if (ret == -1)
			return (ERROR);
		buf[ret] = '\0';
		ft_lstaddback(&list, ft_lstnew(buf, ret + 1));
		if (ft_strchr(buf, '\n'))
			break ;
	}
	if (!list && (!perm[fd] || !perm[fd][0]))
		return (END);
	*line = ft_cpy_line(*line, ft_list_to_str(list), &perm[fd]);
	ft_lstdel(&list, ft_elemdel);
	return (READ);
}*/

static int	stocktoline(char **stock, char **line)
{
	char	*tmp;
	size_t	len;

	len = 0;
	while ((*stock)[len] && (*stock)[len] != '\n')
		len++;
	if (!(*line = ft_strnew(sizeof(**line) * len)))
		return (-1);
	*line = ft_strncpy(*line, *stock, len);
	if (((*stock)[len] && !(*stock)[len + 1]) || !(*stock)[len])
	{
		ft_strdel(stock);
		return (1);
	}
	if (!(tmp = ft_strnew(sizeof(*tmp) * (ft_strlen(*stock) - len - 1))))
		return (-1);
	tmp = ft_strcpy(tmp, *stock + len + 1);
	free(*stock);
	*stock = tmp;
	return (1);
}

/*
** bufftostock copies the content from buffer into stock.
** Returns 1 if everything went well or
** -1 if an error occured.
*/

static int	bufftostock(char *buff, char **stock, size_t size)
{
	size_t	o_len;

	buff[size] = '\0';
	o_len = (*stock ? ft_strlen(*stock) : 0);
	if (!(*stock = ft_realloc(*stock, o_len, o_len + size + 1)))
		return (-1);
	while (size--)
	{
		(*stock)[o_len++] = *buff;
		buff++;
	}
	(*stock)[o_len] = '\0';
	return (ft_strchr(*stock, '\n') ? 1 : 0);
}

/*
** getstock checks if a file struct has been created in the chained list
** corresponding to the fd.
** If it finds one, the char *stock is returned, if not, it returns NULL.
*/

char		*getstock(t_list *file_lst, int fd)
{
	while (file_lst)
	{
		if (((t_file*)file_lst->content)->fd == fd)
			return (((t_file*)file_lst->content)->stock);
		file_lst = file_lst->next;
	}
	return (NULL);
}

/*
** manage_lst replaces the stock in chained list file corresponding
** to the fd. If the reading is over, it deletes the file from the
** list. If no file was found in the list, it creates a new file
** containing the fd and the stock.
*/

void		manage_lst(t_list **file_lst, int fd, char *stock, int ret)
{
	t_file	file;
	t_list	*prec;
	t_list	*tmp;

	file.fd = fd;
	file.stock = stock;
	prec = *file_lst;
	tmp = *file_lst;
	while (tmp && ((t_file*)tmp->content)->fd != fd)
		tmp = tmp->next;
	if (!tmp)
		ft_lstadd(file_lst, ft_lstnew(&file, sizeof(file)));
	else
	{
		((t_file*)tmp->content)->stock = stock;
		while (prec != tmp && prec->next != tmp)
			prec = prec->next;
		if (!stock && !ret)
		{
			prec->next = prec ? tmp->next : prec->next;
			*file_lst = (prec == *file_lst) ? (*file_lst)->next : *file_lst;
			free(tmp->content);
			free(tmp);
		}
	}
}

int			get_next_line(int fd, char **line)
{
	char			*buff;
	static t_list	*file_lst = NULL;
	char			*stock;
	ssize_t			ret;
	int				flg;

	if (fd < 0 || BUFF_SIZE == 0)
		return (-1);
	stock = getstock(file_lst, fd);
	flg = (stock && ft_strchr(stock, '\n')) ? 1 : 0;
	if (!(buff = (char*)ft_memalloc(sizeof(char) * (BUFF_SIZE + 1))))
		return (-1);
	ret = 1;
	while (!flg && (ret = read(fd, buff, BUFF_SIZE)) > 0)
		flg = bufftostock(buff, &stock, ret);
	ft_memdel((void**)&buff);
	if (flg == -1 || ret == -1)
		return (-1);
	if (stock)
		flg = stocktoline(&stock, line);
	manage_lst(&file_lst, fd, stock, ret);
	if (flg == 0 && ret == 0)
		return (0);
	return (1);
}
