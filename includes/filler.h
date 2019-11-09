/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 18:36:29 by mguerrea          #+#    #+#             */
/*   Updated: 2019/11/09 13:21:08 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include "get_next_line.h"
# include <stdio.h>

# define RED     "\033[31m"
# define RESET   "\033[0m"

typedef struct	s_pos
{
	int x;
	int y;
}				t_pos;

typedef struct	s_map
{
	char	**tab;
	int		x;
	int		y;
	char	me;
	char	they;
	t_pos	last;
}				t_map;

void			place_piece(t_map *map, t_map *piece);
void			print_map(t_map *map);
void			get_last(t_map *oldmap, t_map *map);
void			get_player(char *str, t_map *map);
t_map			*get_piece(void);
t_map			*get_map(void);
void			free_map(t_map *map);
void			print_pos(t_pos *res);

#endif
