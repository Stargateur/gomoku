#pragma once

#ifndef IGVOBJECT_HPP__
#define IGVOBJECT_HPP__

#include	<SFML/Graphics.hpp>

class IGVObject
{
public:
	virtual				~IGVObject(void) {}
	virtual sf::Sprite*	getSprite(void) = 0;
};

#endif // !IGVOBJECT_HPP__
