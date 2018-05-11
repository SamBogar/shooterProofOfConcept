/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbogar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/08 14:03:39 by sbogar            #+#    #+#             */
/*   Updated: 2017/07/09 23:02:33 by sbogar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Entity.class.hpp"

WINDOW		*instantiate_window( void )
{
	WINDOW	*win;

	win = initscr();
	cbreak();
	keypad(win, TRUE);
	noecho();
	curs_set(FALSE);
	nodelay(win, TRUE);

	return (win);
}

int		main( void )
{
	WINDOW *win;

	srand((unsigned)time(0));
	win = instantiate_window();
	while(play_game(win))
	{
		move(LINES / 2, COLS / 2 - 5);
		printw("Good Game, ur ded");
		wrefresh(win);
		sleep(5);
	}
	endwin();

	return (0);
}
