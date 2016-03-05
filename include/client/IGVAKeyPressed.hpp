#pragma once

#ifndef IGVAKEY_PRESSED_HPP_
#define IGVAKEY_PRESSED_HPP_

#include	<SFML/Graphics.hpp>

class IGVAKeyPressed
{
public:
	virtual ~IGVAKeyPressed(void) {};
	virtual void Act(sf::Sprite &texture, sf::Vector2f const &mousePosition, sf::Uint32 const &key) = 0;
};

#endif // !IGVAKEY_PRESSED_HPP_
