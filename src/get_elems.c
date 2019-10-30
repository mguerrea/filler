/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_elems.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 16:15:22 by mguerrea          #+#    #+#             */
/*   Updated: 2019/10/30 16:16:42 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

t_map *get_size(t_map **elem, int i)
{
	char *str;

	if (get_next_line(0, &str) < 1)
		return (NULL);
	*elem = malloc(sizeof(t_map) * 1);
	(*elem)->y = ft_atoi(str + i);
	while (str[i] != ' ')
		i++;
	i++;
	(*elem)->x = ft_atoi(str + i);
	ft_strdel(&str);
	(*elem)->tab = malloc(sizeof(char *) * ((*elem)->y + 1));
	return(*elem);
}

t_map *get_map(void)
{
	t_map *map;
	char *str;
	int i;

	if (get_size(&map, 8) == NULL)
		return (NULL);
	i = -1;
	get_next_line(0, &str);
	free(str);
	while (++i < map->y)
	{
		get_next_line(0, &str);
		map->tab[i] = ft_strdup(str + 4);
		free(str);
	}
	map->tab[i] = NULL;
	return (map);
}

t_map *get_piece(void)
{
	char *str;
	t_map *piece;
	int i;

	piece = NULL;
	if (get_size(&piece, 6) == NULL)
		return (NULL);
	i = 0;
	while (i < piece->y)
	{
		get_next_line(0, &str);
		piece->tab[i] = ft_strdup(str);
		free(str);
		i++;
	}
	piece->tab[i] = NULL;
	return (piece);
}

void get_player(char *str, t_map *map)
{
	if (ft_strncmp(str, "$$$ exec p2 :", 12) == 0)
		{
			map->me = 'x';
			map->they = 'o';
		}
		else
		{
			map->me = 'o';
			map->they = 'x';
		}
}

void get_last(t_map *oldmap, t_map *map)
{
	int i;
	int j;

	i = -1;
	if (oldmap)
	{
	while (++i < map->y)
	{
		j = -1;
		while (++j < map->x)
		{
			if (oldmap->tab[i][j] == '.' && map->tab[i][j] == map->they - 32)
			{
				map->last.x = j;
				map->last.y = i;
				return ;
			}
		}
	}
	}
	map->last.x = -1;
	map->last.y = -1;
}
