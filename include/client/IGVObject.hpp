#pragma once

#ifndef IGVOBJECT_HPP__
#define IGVOBJECT_HPP__

#include	<SFML/Graphics.hpp>

class IGVObject
{
public:
	virtual					~IGVObject(void) {}
	virtual sf::Drawable*	getDrawable(void) = 0;
	virtual void			mouseClick(sf::Vector2f const &pos) = 0;
	virtual void			mouseMove(sf::Vector2f const & pos) = 0;
};

#endif // !IGVOBJECT_HPP__
