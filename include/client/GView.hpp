#pragma once

#ifndef GVIEW_HPP__
#define GVIEW_HPP__

#include	<list>
#include	<SFML/Graphics.hpp>
#include	"IGVObject.hpp"

class GView
{
public:
	GView();
	~GView();

public:
	void					pushObject(IGVObject *object);
	void					removeObject(IGVObject *object);
	std::list<sf::Sprite *>	getSprites();

	// Events
public:
	void	mouseClick(sf::Vector2f pos);

private:
	std::list<IGVObject *>	mObjects;
};

#endif // !GVIEW_HPP__