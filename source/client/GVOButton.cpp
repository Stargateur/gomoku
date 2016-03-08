#include	"GVOButton.hpp"

GVOButton::GVOButton(sf::Vector2f pos, sf::Texture const &texture, sf::Vector2f const &scale) : mPos(pos), mText(nullptr)
{
	mSprite.setTexture(texture);
	mSprite.setPosition(mPos);
	mSprite.setScale(scale);
}

GVOButton::~GVOButton(void)
{
	for (IGVAMouseHover* action : mHoverActions)
		delete action;
	for (IGVAMouseClick* action : mClickActions)
		delete action;
	for (IGVAKeyPressed* action : mKeyActions)
		delete action;
}

sf::Drawable	*GVOButton::getDrawable(void) { return &mSprite; }
sf::Sprite & GVOButton::getSprite(void) { return mSprite; }
void			GVOButton::addAction(IGVAMouseClick *action) { mClickActions.push_back(action); }
void			GVOButton::addAction(IGVAMouseHover *action) { mHoverActions.push_back(action); }
void			GVOButton::addAction(IGVAKeyPressed *action) { mKeyActions.push_back(action); }

void			GVOButton::mouseClick(sf::Vector2f const & pos)
{
	if (mClickActions.empty() == false)
	{
		for (IGVAMouseClick* action : mClickActions)
			action->Act(mSprite, pos);
	}
}

void			GVOButton::mouseMove(sf::Vector2f const & pos)
{
	if (mHoverActions.empty() == false)
	{
		for (IGVAMouseHover* action : mHoverActions)
			action->Act(mSprite, pos);
	}
}

void			GVOButton::keyPressed(sf::Vector2f const &pos, sf::Uint32 const &key)
{
	for (IGVAKeyPressed* action : mKeyActions)
		action->Act(mSprite, pos, key);
}
