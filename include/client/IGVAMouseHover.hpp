#pragma once

#ifndef IGVAMOUSE_HOVER_HPP_
#define IGVAMOUSE_HOVER_HPP_

#include	<SFML/Graphics.hpp>

class IGVAMouseHover
{
public:
	virtual ~IGVAMouseHover(void) {};
	virtual void Act(sf::Sprite &texture, sf::Vector2f const & const mousePosition) = 0;
};

#endif // !IGVAMOUSE_HOVER_HPP_
