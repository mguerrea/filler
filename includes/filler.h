/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 18:36:29 by mguerrea          #+#    #+#             */
/*   Updated: 2019/09/30 13:20:56 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include "get_next_line.h"
# include <stdio.h>

typedef struct s_map
{
	char **tab;
	int x;
	int y;
	char me;
	char they;
}				t_map;

int		place_piece(t_map *map, t_map *piece);

#endif