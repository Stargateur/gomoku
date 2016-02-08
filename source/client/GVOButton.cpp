#include	"GVOButton.hpp"

GVOButton::GVOButton(sf::Vector2f pos, sf::Texture texture, sf::Vector2f scale) : mPos(pos), mTexture(texture), mScale(scale)
{
	mMainSprite.setTexture(mTexture);
	mMainSprite.setPosition(mPos);
	mMainSprite.setScale(mScale);
	mCurView = &mMainSprite;
}

GVOButton::~GVOButton() {}

sf::Sprite* GVOButton::getSprite(void)
{
	return mCurView;
}

