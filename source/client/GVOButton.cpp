#include	"GVOButton.hpp"

GVOButton::GVOButton(sf::Vector2f pos, sf::Texture const &texture, sf::Vector2f const &scale) : mPos(pos)
{
	mSprite.setTexture(texture);
	mSprite.setPosition(mPos);
	mSprite.setScale(scale);
}

GVOButton::~GVOButton(void) {}

sf::Drawable	*GVOButton::getDrawable(void) { return &mSprite; }
void			GVOButton::addAction(IGVAMouseClick *mouseAction) { mClickActions.push_back(mouseAction); }
void			GVOButton::addAction(IGVAMouseHover *mouseAction) { mHoverActions.push_back(mouseAction); }

void			GVOButton::mouseClick(sf::Vector2f const & const pos)
{
	if (mClickActions.empty() == false)
	{
		for (IGVAMouseClick* action : mClickActions)
			action->Act(mSprite, pos);
	}
}

void			GVOButton::mouseMove(sf::Vector2f const & const pos)
{
	if (mHoverActions.empty() == false)
	{
		for (IGVAMouseHover* action : mHoverActions)
			action->Act(mSprite, pos);
	}
}
