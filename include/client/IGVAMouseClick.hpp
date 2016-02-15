#pragma once

#ifndef IGVAMOUSE_CLICK_HPP_
#define IGVAMOUSE_CLICK_HPP_

#include	<SFML/Graphics.hpp>
#include	"IGVAction.hpp"

class IGVAMouseClick : public IGVAction
{
public:
	virtual ~IGVAMouseClick(void) {};
	virtual void Act(sf::Sprite &texture, sf::Vector2f &mousePosition) = 0;
};

#endif // !IGVAMOUSE_CLICK_HPP_
