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
	mObjects.remove(object);
}

std::list<sf::Sprite *> GView::getSprites()
{
	std::list<sf::Sprite *>res;
	for (IGVObject *obj : mObjects)
	{
		res.push_back(obj->getSprite());
	}
	return res;
}

void GView::mouseClick(sf::Vector2f pos)
{
	for (IGVObject *obj : mObjects)
		obj->mouseClick(pos);
}
