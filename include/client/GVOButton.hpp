#pragma once

#ifndef GVOBUTTON_HPP__
#define GVOBUTTON_HPP__

#include	<SFML/Graphics.hpp>
#include	"IGVObject.hpp"

template<typename T>
class GVOButton : public IGVObject
{
public:
	GVOButton(sf::Vector2f pos, sf::Texture texture, sf::Vector2f scale) : mPos(pos), mTexture(texture), mHoverTexture(texture)
	{
		mMainSprite.setTexture(mTexture);
		mMainSprite.setPosition(mPos);
		mMainSprite.setScale(scale);
		mCurView = &mMainSprite;
		mHoverSprite.setScale(scale);
		mHoverSprite.setTexture(mHoverTexture);
		mHoverSprite.setPosition(mPos);
	}
	GVOButton(sf::Vector2f pos, sf::Texture texture, sf::Vector2f scale, sf::Texture hoverTexture, sf::Vector2f hoverScale) : mPos(pos), mTexture(texture), mHoverTexture(hoverTexture)
	{
		mMainSprite.setTexture(mTexture);
		mMainSprite.setPosition(mPos);
		mMainSprite.setScale(scale);
		mCurView = &mMainSprite;
		mHoverSprite.setScale(hoverScale);
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
		callbackParam = callbackParam;
	}
	void	mouseClick(sf::Vector2f pos)
	{
		if (pos.x >= mPos.x && pos.x <= mPos.x + mTexture.getSize().x && pos.y >= mPos.y && pos.y <= mPos.y + mTexture.getSize().y)
		{
			if (mCallback != NULL)
				(*mCallback)(mCallbackParam);
		}
	}
	void	mouseMove(sf::Vector2f pos)
	{
		if (pos.x >= mPos.x && pos.x <= mPos.x + mTexture.getSize().x && pos.y >= mPos.y && pos.y <= mPos.y + mTexture.getSize().y)
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
	sf::Vector2f	mPos;
	T				mCallbackParam;
	void			(*mCallback)(T param);
};

#endif // !GVOBUTTON_HPP__
