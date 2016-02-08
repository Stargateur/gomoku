#include	"GView.hpp"

GView::GView()
{
}

GView::~GView()
{
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
