/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Entity.class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbogar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/08 19:40:21 by sbogar            #+#    #+#             */
/*   Updated: 2017/07/09 22:58:43 by sbogar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENTITY_CLASS_H
# define ENTITY_CLASS_H

#include <iostream>
#include <ncurses.h>
#include <unistd.h>
# define ENEMY_MOVE_SPEED 333
# define ENEMY_FREQUENCY 9999
# define BULLET_FREQUENCY 2
# define SECS_PER_TICK 0.00000000001
# define LINES 60 
# define COLS 60 

# define ESC 27
# define SPACE 32

/*
** to increase rate at which specific enemies spawn, 
** change the acceptable ranges in print_map/populate_first_line()

** to increase the specific move speed of an enemy type, increase acceptable range for timer
** in play_game/redraw()
*/

enum	e_xy{
	X,
	Y
};

class Entity {

public:

int		score;

Entity( void );
Entity(int _x, int _y, int _health, char _avatar);
Entity( Entity & src);
~Entity(void);

Entity & operator=(Entity & src);

char	avatar;
int		x;
int		y;
int		pos[3][2];
int		health;
};

int					play_game(WINDOW *win);
int					move_objects(char map[LINES][COLS], Entity * player, char enemy_type);
void				print_map(char map[LINES][COLS], Entity * player);
void				populate_first_line(char map[LINES][COLS]);
int					clear_map(char map[LINES][COLS]);

#endif
