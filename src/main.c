/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 18:08:28 by mguerrea          #+#    #+#             */
/*   Updated: 2019/10/03 15:16:41 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "filler.h"

// write Y X\n

t_map *get_map()
{
	t_map *map;
	char *str;
	int i;

	if (get_next_line(0, &str) < 1)
		return (NULL);
	map = malloc(sizeof(t_map) * 1);
	i = 8;
	map->y = ft_atoi(str + i);
	while (str[i] != ' ')
		i++;
	i++;
	map->x = ft_atoi(str + i);
	free(str);
	//	dprintf(2, "x = %d\ty = %d\n", map->x, map->y);
	map->tab = malloc(sizeof(char *) * (map->y + 1));
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

t_map *get_piece()
{
	char *str;
	t_map *piece;
	int i;

	get_next_line(0, &str);
	piece = malloc(sizeof(t_map) * 1);
	i = 6;
	piece->y = ft_atoi(str + i);
	while (str[i] != ' ')
		i++;
	i++;
	piece->x = ft_atoi(str + i);
	free(str);
	//	dprintf(2, "x = %d\ty = %d\n", piece->x, piece->y);
	piece->tab = malloc(sizeof(char *) * (piece->y + 1));
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

int main()
{
	t_map *map;
	t_map *piece;
	char *str;
//	char me;
//	char they;

	str = NULL;
	get_next_line(0, &str);
	{
/*		if (ft_strncmp(str, "$$$ exec p2 :", 12) == 0)
		{
			me = 'x';
			they = 'o';
		}
		else
		{
			me = 'o';
			they = 'x';
		}
		free(str);*/
	}
	while (1)
	{
		if (!(map = get_map()))
			break;
	//	map->me = me;
	//	map->they = they;
		get_player(str, map);
		piece = get_piece();

		if (place_piece(map, piece) == 0)
			ft_putstr("0 0\n");
	}
	ft_strdel(&str);
}