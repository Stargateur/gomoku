#pragma once

#ifndef GOMOKU_GRAPHICS_HPP_
#define	GOMOKU_GRAPHICS_HPP_

#include	<SFML/Graphics.hpp>
#include	<SFML/Audio.hpp>
#include	<iostream>
#include	"GView.hpp"

#define		WIN_X (1080)
#define		WIN_Y (720)

class GomokuGraphics
{
public:
	enum e_view
	{
		HOME = 0,
		PLAY
	};

public:
	GomokuGraphics(void);
	~GomokuGraphics(void);
	void	init(void);
	void	reset(void);
	void	run(void);
	void	affStone(void);

private:
	void	checkClientUpdates(void);
	void	updateView(void);

private:
	sf::RenderWindow	*mWindow;
	//sf::Sprite			mBackground;
	GView				*mCurrentView;
	GView				mMenuView;
	GView				mHomeView;
	GView				mGameView;
	GView				mConnectView;
	sf::Music			mThemeSound;
	IGVObject			*mStones[19][19];
};

#endif // !GOMOKU_GRAPHICS_HPP_
