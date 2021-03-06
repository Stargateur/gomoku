#include	"GView.hpp"

GView::GView()
{
}

GView::~GView()
{
	for (IGVObject *object : mObjects)
		delete object;
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

void GView::clearObjects(void)
{
	for (IGVObject *object : mObjects)
		delete object;
	mObjects.clear();
}

std::list<sf::Drawable *> GView::getDrawables()
{
	sf::Drawable				*dwbl;
	std::list<sf::Drawable *>	res;
	for (IGVObject *obj : mObjects)
	{
		dwbl = obj->getDrawable();
		if (dwbl != nullptr)
			res.push_back(dwbl);
	}
	return res;
}

void GView::mouseClick(sf::Vector2f const &pos)
{
	for (IGVObject *obj : mObjects)
		obj->mouseClick(pos);
}

void GView::mouseMove(sf::Vector2f const &pos)
{
	for (IGVObject *obj : mObjects)
		obj->mouseMove(pos);
}

void GView::keyPressed(sf::Vector2f const &pos, sf::Uint32 const &key)
{
	for (IGVObject *obj : mObjects)
		obj->keyPressed(pos, key);
}