#include "GameInfo.hpp"

GameInfo::GameInfo()
{
}

GameInfo::~GameInfo()
{
}

void GameInfo::reset()
{
	mHisto.clear();
	for (int x = 0; x < 19; x++)
		for (int y = 0; y < 19; y++)
			mPlate[x][y] = ITCP_protocol<GameInfo>::Game_stone::Color::None;
	mSpecs = 0;
	mOpponent.clear();
	mGameEnd = false;
	mConnected = false;
}
