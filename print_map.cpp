/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbogar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/08 21:06:23 by sbogar            #+#    #+#             */
/*   Updated: 2017/07/09 21:48:18 by sbogar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Entity.class.hpp"

void				print_map(char map[LINES][COLS], Entity * player)
{
	int				x;
	int				y;
	int				col;

	x = -1;
	y = -1;
	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	init_pair(4, COLOR_CYAN, COLOR_BLACK);
	while (++y < LINES)
	{
		x = -1;
		while (++x < COLS)
		{
			mvdelch(y, x);
			col = 0;
			if (map[y][x] == '*')
				col = 1;
			else if (map[y][x] == '#')
				col = 2;
			else if (map[y][x] == 'o')
				col = 3;
			else if (map[y][x] == '|')
				col = 4;
			attron(COLOR_PAIR(col));
			mvaddch(y, x, map[y][x]);
			attroff(COLOR_PAIR(col));
		}
	}
	attron(COLOR_PAIR(4));
	mvaddch(player->y, player->x, player->avatar);
	mvaddch(player->y, player->x + 1, player->avatar);
	mvaddch(player->y, player->x - 1, player->avatar);
	mvaddch(player->y - 1, player->x, player->avatar);
	attroff(COLOR_PAIR(4));
}

/*
** to increase rate at which enemies spawn, change the acceptable ranges here
*/

void				populate_first_line(char map[LINES][COLS])
{
	unsigned int	random;	
	int				i;

	i = 0;
	while (i < COLS)
	{
		random = rand() % ENEMY_FREQUENCY;
		if (map[0][i] == ' ' || map[0][i] == '|')
		{
			if (random <= 5 && map[1][i] == ' ' && map[1][i + 1] == ' ')
			{
				map[0][i] = '*';
				map[1][i] = '*';
				map[0][i + 1] = '*';
				map[1][i + 1] = '*';
				i += 1;
			}
			else if (random  >= 6 && random <= 8 && map[1][i] == ' ')
			{
				map[0][i] = 'o';
				map[0][i + 1] = 'o';
				map[0][i + 2] = 'o';
				map[1][i] = 'o';
				i += 2;		
			}
			else if (random >= 9 && random <= 10 && map[1][i + 1] == ' ')
			{
				map[0][i] = '#';
				map[0][i + 1] = '#';
				map[0][i + 2] = '#';
				map[1][i + 1] = '#';
				i+= 3;
			}
			else
				map[0][i] = ' ';
		}
		i++;
	}
}

