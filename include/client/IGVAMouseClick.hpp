#pragma once

#ifndef IGVAMOUSE_CLICK_HPP_
#define IGVAMOUSE_CLICK_HPP_

#include	<SFML/Graphics.hpp>


class IGVAMouseClick
{
public:
	virtual ~IGVAMouseClick(void) {};
	virtual void Act(sf::Sprite &texture, sf::Vector2f const &mousePosition) = 0;
};

#endif // !IGVAMOUSE_CLICK_HPP_
