/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 18:08:28 by mguerrea          #+#    #+#             */
/*   Updated: 2019/10/30 14:36:41 by mguerrea         ###   ########.fr       */
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

/*void get_last(t_map *map)
{
	int i;
	int j;

	i = 0;
	dprintf(2, RED "map they = %c\n" RESET, map->they);
	print_map(map);
	while (i < map->y)
	{
		j = 0;
		while (j < map->x)
		{
			if (map->tab[i][j] == map->they)
			{
				dprintf(2, "jpp\n");
				map->last.x = j;
				map->last.y = i;
				return ;
			}
			j++;
		}
		i++;
	}

}*/

void get_last(t_map *oldmap, t_map *map)
{
	int i;
	int j;

	i = 0;
	if (oldmap)
	{
	while (i < map->y)
	{
		j = 0;
		while (j < map->x)
		{
			if (oldmap->tab[i][j] == '.' && map->tab[i][j] == map->they - 32)
			{
				map->last.x = j;
				map->last.y = i;
				return ;
			}
			j++;
		}
		i++;
	}
	}
	map->last.x = -1;
	map->last.y = -1;
}

int main()
{
	t_map *map;
	t_map *oldmap;
	t_map *piece;
	char *str;

	str = NULL;
	oldmap = NULL;
	get_next_line(0, &str);
	while (1)
	{
		if (!(map = get_map()))
			break;
		get_player(str, map);
		get_last(oldmap, map);
		piece = get_piece();
		place_piece(map, piece);
		// we have to free oldmap
		oldmap = map;
	}
	ft_strdel(&str);
}