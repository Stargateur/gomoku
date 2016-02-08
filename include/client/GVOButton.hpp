#pragma once

#ifndef GVOBUTTON_HPP__
#define GVOBUTTON_HPP__

#include	<SFML/Graphics.hpp>
#include	"IGVObject.hpp"

class GVOButton : public IGVObject
{
public:
	GVOButton(sf::Vector2f pos, sf::Texture texture, sf::Vector2f scale);
	virtual ~GVOButton();
	virtual sf::Sprite*	getSprite(void);

private:
	sf::Sprite		*mCurView;
	sf::Sprite		mMainSprite;
	sf::Texture		mTexture;
	sf::Vector2f	mPos;
	sf::Vector2f	mScale;
};

#endif // !GVOBUTTON_HPP__
