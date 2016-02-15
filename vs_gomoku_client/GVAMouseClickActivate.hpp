#pragma once

#ifndef GVAMOUSECLICKACTIVATE_HPP_
#define GVAMOUSECLICKACTIVATE_HPP_

#include	<SFML/Graphics.hpp>
#include	"IGVAMouseClick.hpp"

class GVAMouseClickActivate : public IGVAMouseClick
{
public:
	GVAMouseClickActivate(void) {};
	virtual ~GVAMouseClickActivate(void) {}
	virtual void Act(sf::Sprite &texture, sf::Vector2f &mousePosition) {}

private:

};

#endif // !GVAMOUSECLICKACTIVATE_HPP_
