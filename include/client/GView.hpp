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
	std::list<sf::Sprite *>	getSprites();

private:
	std::list<IGVObject *>	mObjects;
};

#endif // !GVIEW_HPP__
