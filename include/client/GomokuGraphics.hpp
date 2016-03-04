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
	GomokuGraphics(void);
	~GomokuGraphics(void);
	void	init(void);
	void	reset(void);
	void	run(void);
	void	affStone(void);

private:
	void	checkClientUpdates(void);

private:
	sf::RenderWindow	*mWindow;
	//sf::Sprite			mBackground;
	GView				*mCurrentView;
	GView				mMenuView;
	GView				mGameView;
	GView				mConnectView;
	IGVObject			*mStones[19][19];
};

#endif // !GOMOKU_GRAPHICS_HPP_
