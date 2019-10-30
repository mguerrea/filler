/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 12:39:28 by mguerrea          #+#    #+#             */
/*   Updated: 2019/10/30 14:36:57 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int overlap(t_map *map, t_map *piece, int i, int j)
{
	int k;
	int l;
	int overlap;

	k = 0;
	overlap = 0;
	while (k < piece->y)
	{
		l = 0;
		while (l < piece->x)
		{
			if (piece->tab[k][l] == '*' && (k+i >= map->y || l+j >= map->x))
				return (-1);
			if (piece->tab[k][l] == '*' && (k+i < 0 || l+j < 0))
				return (-1);
			if (piece->tab[k][l] == '*' && (map->tab[k+i][l+j] == map->they || map->tab[k+i][l+j] == map->they - 32))
				return(-1);
			if (piece->tab[k][l] == '*' && (map->tab[k+i][l+j] == map->me || map->tab[k+i][l+j] == map->me - 32))
				overlap += 1;
			l++;
		}
		k++;
	}
	return (overlap);
}

int		check_place(t_map *map, t_map *piece, int i, int j)
{
	int ret;

	if ((ret = overlap(map, piece, i, j)) != 1)
	{
	//	dprintf(2, "ret = %d\n", ret);
		return (0);
	}
	return (1);
}

void is_better(int i, int j, t_pos **res, t_map *map)
{
	int norm2;
	int norm1;

	norm2 = (map->last.x - j)*(map->last.x - j) + (map->last.y - i)*(map->last.y - i);
	if (*res != NULL && map->last.x != -1)
	{
		norm1 = ((*res)->x - j)*((*res)->x - j) + ((*res)->y - i)*((*res)->y - i);
		if (norm2 < norm1)
		{
			(*res)->x = j;
			(*res)->y = i;
		}
	}
	else if (*res == NULL)
	{
	//	dprintf(2, "ELSE\n");
		*res = (t_pos *)malloc(sizeof(t_pos) * 1);
		(*res)->x = j;
		(*res)->y = i;
	//	dprintf(2, "res x = %d\t res y = %d\n", (*res)->x, (*res)->y);
	}
	
}

void print_pos(t_pos *res)
{
	if (res == NULL)
		ft_putstr("0 0\n");
	else
	{
		ft_putnbr(res->y);
		ft_putchar(' ');
		ft_putnbr(res->x);
		ft_putchar('\n');
	}
	free(res);
}

void	place_piece(t_map *map, t_map *piece)
{
	int i;
	int j;
	t_pos *res;
	
	i = 0 - piece->x;
	res = NULL;
	while (i < map->y)
	{
		j = 0 - piece->y;
		while (j < map->x)
		{
			if (check_place(map, piece, i, j))
				is_better(i, j, &res, map);
			j++;
		}
		i++;
	}
	print_pos(res);
}