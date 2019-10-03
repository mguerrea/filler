/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 12:39:28 by mguerrea          #+#    #+#             */
/*   Updated: 2019/10/03 15:28:46 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

// TO DO : CHECK FIRST PLAYER

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

int		place_piece(t_map *map, t_map *piece)
{
	int i;
	int j;
	
	i = 0;
	while (i < map->y)
	{
		j = 0 - piece->y;
		while (j < map->x)
		{
			if (check_place(map, piece, i, j))
			{
	//			dprintf(2, "i = %d\tj = %d\n", i, j);
				ft_putnbr(i);
				ft_putchar(' ');
				ft_putnbr(j);
				ft_putchar('\n');
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}