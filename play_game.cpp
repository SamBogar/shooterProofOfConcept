/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_game.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbogar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/08 17:17:41 by sbogar            #+#    #+#             */
/*   Updated: 2017/07/09 23:02:13 by sbogar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Entity.class.hpp"

void				adjust_player(int key, Entity * player, bool undo)
{
	if (undo)
	{
		player->x = (key == KEY_LEFT) ? ++player->x : player->x;
		player->x = (key == KEY_RIGHT) ? --player->x : player->x;
		player->y = (key == KEY_UP) ? ++player->y : player->y;
		player->y = (key == KEY_DOWN) ? --player->y : player->y;
	}
	else
	{
		player->x = (key == KEY_LEFT) ? --player->x : player->x;
		player->x = (key == KEY_RIGHT) ? ++player->x : player->x;
		player->y = (key == KEY_UP) ? --player->y : player->y;
		player->y = (key == KEY_DOWN) ? ++player->y : player->y;
	}
}

int				clear_map(char map[LINES][COLS])
{
	int			x;
	int			y;

	y = -1;
	while (++y < LINES)
	{
		x = -1;
		while (++x < COLS)
			map[y][x] = ' ';
	}
	return (0);
}

int				refresh_window(char map[LINES][COLS], Entity * player, int timer)
{
	int			player_died;

	player_died = 0;
	if (timer >= 0 && timer <= 1)	
		player_died += move_objects(map, player, '*');
	if (timer >= 2 && timer <= 4)
		player_died += move_objects(map, player, 'o');
	if (timer >= 5 && timer <= 5)
		player_died += move_objects(map, player, '#');
	if (timer >= 6 && timer <= 10)
		player_died += move_objects(map, player, '.');
	if (timer >= 10 && timer <= 11)
		move_objects(map, player, '|');

	return (player_died);
}

/*
** to increase move speed, increase acceptable range for timer
*/

void				check_for_lines(char map[LINES][COLS], Entity * player)
{
	int				y;
	int				x;
	int				symbols;

	y = -1;
	while ( ++y < LINES )
	{
		x = -1;
		symbols = 0;
		while (++x < COLS )
			if (map[y][x] != ' ')
				symbols++;
		if (symbols == x )
		{
			player->score += 100;
			x = -1;
			while (++x < COLS)
				map[y][x] = ' ';
		}
	}
}

int					redraw(int key, Entity * player,
							char map[LINES][COLS], int timer)
{
	int				is_dead;

	if (key == KEY_LEFT || key == KEY_RIGHT || key == KEY_UP || key == KEY_DOWN)
	{
		move_objects(map, player, '|');
		mvdelch(player->y, player->x);
		adjust_player(key, player, FALSE);
		if (player->x < 1 || player->x > COLS - 2 || player->y < 1 || player->y > LINES - 1)
			adjust_player(key, player, TRUE);
	}
	else if (key == SPACE)
	{
		//map[player->y - 2][player->x] = '|';
		map[player->y - 1][player->x + 1] = '|';
		map[player->y - 1][player->x - 1] = '|';
	}
	is_dead = refresh_window(map, player, timer);
	if (is_dead)
		clear_map(map);
	check_for_lines(map, player);
	print_map(map, player);
	return (is_dead);
}

int					play_game(WINDOW *win)
{
	Entity 			player(COLS / 2, LINES - 1, 3, '^');
	char			map[LINES][COLS];
	int				key;
	unsigned int	t;
	unsigned int	prev_t;
	unsigned int	init_t;
	int				i;

	i = 0;
	init_t = clock();
	prev_t = clock();
	player.pos[0][X] = -1;
	player.pos[0][Y] = 0;
	player.pos[1][X] = 1;
	player.pos[1][Y] = 0;
	player.pos[2][X] = 0;
	player.pos[2][Y] = -1;
	while (1)
	{
		t = clock();
		if ((double)(t - prev_t) / (double)CLOCKS_PER_SEC > SECS_PER_TICK)
		{
			prev_t = t;
			key = getch();
			if (key == ESC)
				return (0);
			if(redraw(key, &player, map, i % ENEMY_MOVE_SPEED))
			{
				init_t = t;
				if (player.health <= 0)
				{
					clear_map(map);
					return (1);
				}
			}
			wrefresh(win);
			i++;
		}
		move(LINES + 1, 0);

		attron(A_REVERSE);
		attron(A_BOLD);
		printw("lives: %d\t", player.health);
		printw("score: %d\t", player.score);
		printw("timer: %.4f\t", (double)(t - init_t) / (double)CLOCKS_PER_SEC);
		attroff(A_REVERSE);
		attron(A_BOLD);
	}
	return (0);
}
