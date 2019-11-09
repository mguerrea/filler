/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 18:08:28 by mguerrea          #+#    #+#             */
/*   Updated: 2019/11/09 12:55:41 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "filler.h"

int	main(void)
{
	t_map	*map;
	t_map	*oldmap;
	t_map	*piece;
	char	*str;

	str = NULL;
	oldmap = NULL;
	get_next_line(0, &str);
	while (1)
	{
		if (!(map = get_map()))
			break ;
		get_player(str, map);
		get_last(oldmap, map);
		if ((piece = get_piece()) == NULL)
			break ;
		place_piece(map, piece);
		free_map(oldmap);
		free_map(piece);
		oldmap = map;
	}
	ft_strdel(&str);
}
