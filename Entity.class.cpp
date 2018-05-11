/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Entity.class.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbogar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/08 19:40:29 by sbogar            #+#    #+#             */
/*   Updated: 2017/07/09 22:24:21 by sbogar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Entity.class.hpp"


Entity::Entity( void ): avatar(' '),\
						x(-1),
						y(-1), \
						health(-1)
{
}

Entity::Entity(int _x, int _y, int _hp, char _avatar): score(0), \
														avatar(_avatar), \
														x(_x), \
													   y(_y), \
													   health(_hp) 
{
  	return;
}

Entity::~Entity(void) {
  return;
}

Entity::Entity( Entity & src )
{
	this->avatar = src.avatar;
	this->x = src.x;
	this->y = src.y;
	this->health = src.health;
}

Entity & Entity::operator=( Entity & src )
{
	this->avatar = src.avatar;
	this->x = src.x;
	this->y = src.y;
	this->health = src.health;

	return (*this);
}
