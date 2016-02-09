#pragma once

#ifndef GOMOKU_GRAPHICS_HPP_
#define	GOMOKU_GRAPHICS_HPP_

#include	<SFML/Graphics.hpp>
#include	<iostream>
#include	"GView.hpp"

#define		WIN_X (1080)
#define		WIN_Y (720)

class GomokuGraphics
{
public:
	GomokuGraphics();
	~GomokuGraphics();
	void init();
	void run();
	void affStone();

private:
	void	checkClientUpdates(void);

private:
	sf::RenderWindow	*mWindow;
	sf::Texture			mTextureBackground;
	sf::Sprite			mBackground;
	sf::Texture			mTopTexture;
	sf::Sprite			mTopMenu;
	sf::Texture			mBlackTexture;
	sf::Texture			mWhiteTexture;
	GView				*mCurrentView;
	GView				mGameView;
	GView				mConnectView;
	IGVObject			*mStones[19][19];
};

#endif // !GOMOKU_GRAPHICS_HPP_
