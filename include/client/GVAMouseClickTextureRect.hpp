#pragma once

#ifndef MOUSECLICKTEXTURERECT_HPP_
#define MOUSECLICKTEXTURERECT_HPP_

#include	<iostream>
#include	<SFML/Graphics.hpp>
#include	"IGVAMouseClick.hpp"

class GVAMouseClickTextureRect : public IGVAMouseClick
{
public:
	GVAMouseClickTextureRect(sf::IntRect const &rect, sf::IntRect const &baserect, bool state = false) : mRect(rect), mBaseRect(baserect), mState(state) {}
	virtual ~GVAMouseClickTextureRect() {}
	virtual void Act(sf::Sprite &texture, sf::Vector2f const &mousePosition)
	{
		if (mousePosition.x >= texture.getGlobalBounds().left && mousePosition.x <= texture.getGlobalBounds().left + texture.getGlobalBounds().width &&
			mousePosition.y >= texture.getGlobalBounds().top && mousePosition.y <= texture.getGlobalBounds().top + texture.getGlobalBounds().height)
		{
			if (mState)
				texture.setTextureRect(mBaseRect);
			else
				texture.setTextureRect(mRect);
			mState = !mState;
		}
	}

private:
	bool		mState;
	sf::IntRect	mRect;
	sf::IntRect	mBaseRect;
};

#endif // !MOUSECLICKTEXTURERECT_HPP_
