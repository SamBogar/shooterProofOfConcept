/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_objects.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbogar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/08 18:11:16 by sbogar            #+#    #+#             */
/*   Updated: 2017/07/09 22:24:31 by sbogar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Entity.class.hpp"

void		reset_ent(Entity * src)
{
	src->avatar = ' ';
	src->health = -1;
	src->x		= -1;
	src->y		= -1;
}

void				move_one(char map[LINES][COLS], int x, int y, int inc, Entity * player)
{
	if (y != ((inc == 1) ? LINES - 1 : 0))
	{
		if (map[y + inc][x] == ' ' || map[y][x] == '.')
		{
			map[y + inc][x] = map[y][x];
			map[y][x] = ' ';
		}
		else if (inc == -1)
		{
			map[y + inc][x] = ' ';
			map[y][x] = ' ';
			player->score++;
		}
	}
}

void				move_enemies(char map[LINES][COLS], Entity * player, char e_type)
{
	int				x;
	int				y;
	
	y = LINES + 1;
	while ( --y >= 0 )
	{
		x = COLS + 1;
		while ( --x >= 0 )
			if (map[y][x] == e_type)
			{
				move_one(map, x, y, 1, player);
				if (e_type == '#' && rand() % BULLET_FREQUENCY == 0 &&
						((x == player->x) ||
							(x == player->x + 1) ||
								(x == player->x - 1)))
					map[y][x + 1] = '.';
			}
	}
}

void				move_bullets(char	 map[LINES][COLS], Entity * player)
{
	int				x;
	int				y;
	
	y = -1;
	while (++y < LINES)
	{
		x = -1;
		while(++x < COLS)
			if (map[y][x] == '|')
				move_one(map, x, y, -1, player);
	}
}

int					move_objects(char map[LINES][COLS], Entity * player, char e_type)
{
	if (e_type != '|')
		move_enemies(map, player, e_type);
	else
		move_bullets(map, player);
	populate_first_line(map);
	if ((map[player->y][player->x] != ' ') ||
		(map[player->y + player->pos[0][Y]][player->x + player->pos[0][X]] != ' ') ||
		 (map[player->y + player->pos[1][Y]][player->x + player->pos[1][X]] != ' ' && 
		  		map[player->y + player->pos[2][Y]][player->x + player->pos[2][X]] != '|') ||
		 	(map[player->y][player->x + 1] != ' '))
	{
	   player->health--;	
	   player->x = COLS / 2;
	   player->y = LINES - 1;
	   return (1);
	}
	return (0);
}
