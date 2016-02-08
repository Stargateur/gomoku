#pragma once

#ifndef GOMOKU_GRAPHICS_HPP_
#define	GOMOKU_GRAPHICS_HPP_

#include	<SFML/Graphics.hpp>
#include	<iostream>
#include	"GView.hpp"

#define		WIN_X (1920)
#define		WIN_Y (1080)

class GomokuGraphics
{
public:
	GomokuGraphics();
	~GomokuGraphics();
	void init();
	void run();

private:
	sf::RenderWindow	*mWindow;
	sf::Texture			mTextureBackground;
	sf::Sprite			mBackground;
	sf::Texture			mTopTexture;
	sf::Sprite			mTopMenu;
	GView				mView;
};

#endif // !GOMOKU_GRAPHICS_HPP_
