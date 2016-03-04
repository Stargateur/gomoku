#include	"GView.hpp"

GView::GView()
{
}

GView::~GView()
{
}

void GView::pushObject(IGVObject * object)
{
	mObjects.push_back(object);
}

void GView::removeObject(IGVObject * object)
{
	if (object != nullptr)
		mObjects.remove(object);
}

#include <iostream>
std::list<sf::Drawable *> GView::getDrawables()
{
	std::list<sf::Drawable *>res;
	for (IGVObject *obj : mObjects)
	{
		res.push_back(obj->getDrawable());
	}
	return res;
}

void GView::mouseClick(sf::Vector2f &pos)
{
	for (IGVObject *obj : mObjects)
		obj->mouseClick(pos);
}

void GView::mouseMove(sf::Vector2f &pos)
{
	for (IGVObject *obj : mObjects)
		obj->mouseMove(pos);
}