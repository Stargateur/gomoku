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
		HOME,
		PLAY,
		CLIENT_OPTIONS,
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
	void	backgroundEffects(void);
	void	showGames(int page);

private:
	sf::RenderWindow	*mWindow;
	sf::Sprite			mBackground;
	sf::Clock			mClock;
	GView				*mCurrentView;
	GView				mMenuView;
	GView				mHomeView;
	GView				mConnectView;
	GView				mGameListView;
	GView				mGameView;
	GView				mClientOptions;
	sf::Music			mThemeSound;
	IGVObject			*mStones[19][19];
};

#endif // !GOMOKU_GRAPHICS_HPP_
