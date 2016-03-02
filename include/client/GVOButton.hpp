#pragma once

#ifndef GVOBUTTON_HPP__
#define GVOBUTTON_HPP__

#include	<SFML/Graphics.hpp>
#include	<list>
#include	"IGVObject.hpp"
#include	"GVAMouseClickCallBack.hpp"

template<typename T>
class GVOButton : public IGVObject
{
public:
	GVOButton(sf::Vector2f pos, sf::Texture texture, sf::Vector2f scale) : mPos(pos), mTexture(texture), mScale(scale)
	{
		mMainSprite.setTexture(mTexture);
		mMainSprite.setPosition(mPos);
		mMainSprite.setScale(mScale);
		mCurView = &mMainSprite;
	}
	virtual ~GVOButton() {}
	virtual sf::Sprite*	getSprite(void)
	{
		return mCurView;
	}

public:
	void	addAction(IGVAMouseClick *mouseAction)
	{
		mClickActions.push_back(mouseAction);
	}
	void	mouseClick(sf::Vector2f pos)
	{
		if (mClickActions.empty() == false)
		{
			for (IGVAMouseClick* action : mClickActions)
				action->Act(*mCurView, pos);
		}
		std::cout << "scalex:" << mCurView->getGlobalBounds().intersects(sf::FloatRect(pos, sf::Vector2f(1,1))) << std::endl;
		
	}
	void	mouseMove(sf::Vector2f pos)
	{
		/**/
	}

private:
	sf::Sprite					*mCurView;
	sf::Sprite					mMainSprite;
	sf::Texture					mTexture;
	sf::Vector2f				mScale;
	sf::Vector2f				mPos;
	std::list<IGVAMouseClick *>	mClickActions;
};

#endif // !GVOBUTTON_HPP__
