/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 12:03:42 by mguerrea          #+#    #+#             */
/*   Updated: 2019/11/09 13:03:09 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	print_map(t_map *map)
{
	int i;

	i = 0;
	while (i < map->y)
	{
		dprintf(2, RED "%s\n" RESET, map->tab[i]);
		i++;
	}
}

void	free_map(t_map *map)
{
	int i;

	if (map == NULL)
		return ;
	i = 0;
	while (i < map->y)
	{
		ft_strdel(&(map->tab[i]));
		i++;
	}
	free(map->tab);
	free(map);
}

void	print_pos(t_pos *res)
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
