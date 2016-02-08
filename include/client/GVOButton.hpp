#pragma once

#ifndef GVOBUTTON_HPP__
#define GVOBUTTON_HPP__

#include	<SFML/Graphics.hpp>
#include	"IGVObject.hpp"

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
	void	setAction(void(*callback)(T param), T callbackParam)
	{
		mCallback = callback;
		callbackParam = callbackParam;
	}
	void	mouseClick(sf::Vector2f pos)
	{
		if (pos.x >= mPos.x && pos.x <= mPos.x + mScale.x)
		{
			if (pos.y >= mPos.y && pos.y <= mPos.y + mScale.y)
				(*mCallback)(mCallbackParam);
		}
	}

private:
	sf::Sprite		*mCurView;
	sf::Sprite		mMainSprite;
	sf::Texture		mTexture;
	sf::Vector2f	mPos;
	sf::Vector2f	mScale;
	T				mCallbackParam;
	void			(*mCallback)(T param);
};

#endif // !GVOBUTTON_HPP__
