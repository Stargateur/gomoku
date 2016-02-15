#pragma once

#ifndef GVOCHECKBOX_HPP__
#define GVOCHECKBOX_HPP__

#include	<SFML/Graphics.hpp>
#include	"IGVObject.hpp"

template<typename T>
class GVOCheckbox : public IGVObject
{
public:
	GVOCheckbox(sf::Vector2f pos, sf::Texture texture, sf::Vector2f scale) : mPos(pos), mTexture(texture), mHoverTexture(texture),
		mScale(scale), mHoverScale(scale), mCallback(nullptr)
	{
		mMainSprite.setTexture(mTexture);
		mMainSprite.setPosition(mPos);
		mMainSprite.setScale(mScale);
		mCurView = &mMainSprite;
		mHoverSprite.setScale(mScale);
		mHoverSprite.setTexture(mHoverTexture);
		mHoverSprite.setPosition(mPos);
	}
	GVOButton(sf::Vector2f pos, sf::Texture texture, sf::Vector2f scale, sf::Texture hoverTexture, sf::Vector2f hoverScale) : mPos(pos),
		mTexture(texture), mHoverTexture(hoverTexture), mScale(scale), mHoverScale(hoverScale)
	{
		mMainSprite.setTexture(mTexture);
		mMainSprite.setPosition(mPos);
		mMainSprite.setScale(mScale);
		mCurView = &mMainSprite;
		mHoverSprite.setScale(mHoverScale);
		mHoverSprite.setTexture(mHoverTexture);
		mHoverSprite.setPosition(mPos);
	}
	virtual ~GVOButton() {}
	virtual sf::Sprite*	getSprite(void)
	{
		return mCurView;
	}

public:
	void	setAction(void(*callback)(T param), T callbackParam)
	{
		mCallback = callback;
		mCallbackParam = callbackParam;
	}
	void	mouseClick(sf::Vector2f pos)
	{
		std::cout << "scalex:" << mCurView->getGlobalBounds().intersects(sf::FloatRect(pos, sf::Vector2f(1, 1))) << std::endl;
		if (pos.x >= mCurView->getGlobalBounds().left && pos.x <= mCurView->getGlobalBounds().left + mCurView->getGlobalBounds().width &&
			pos.y >= mCurView->getGlobalBounds().top && pos.y <= mCurView->getGlobalBounds().top + mCurView->getGlobalBounds().height)
		{
			if (mCallback != nullptr)
				(*mCallback)(mCallbackParam);
		}
	}
	void	mouseMove(sf::Vector2f pos)
	{
		if (pos.x >= mCurView->getGlobalBounds().left && pos.x <= mCurView->getGlobalBounds().left + mCurView->getGlobalBounds().width &&
			pos.y >= mCurView->getGlobalBounds().top && pos.y <= mCurView->getGlobalBounds().top + mCurView->getGlobalBounds().height)
			mCurView = &mHoverSprite;
		else
			mCurView = &mMainSprite;
	}

private:
	sf::Sprite		*mCurView;
	sf::Sprite		mMainSprite;
	sf::Sprite		mHoverSprite;
	sf::Texture		mTexture;
	sf::Texture		mHoverTexture;
	sf::Vector2f	mScale;
	sf::Vector2f	mHoverScale;
	sf::Vector2f	mPos;
	T				mCallbackParam;
	void(*mCallback)(T param);
};

#endif // !GVOBUTTON_HPP__
