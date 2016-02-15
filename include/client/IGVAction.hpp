#pragma once

#ifndef IGVACTION_HPP_
#define IGVACTION_HPP_

#include	<SFML/Graphics.hpp>

class IGVAction
{
public:
	virtual ~IGVAction(void) {};
	virtual void Act(sf::Sprite &texture, sf::Vector2f &mousePosition) = 0;
};

#endif // !IGVACTION_HPP_
