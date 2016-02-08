#pragma once

#ifndef  GAMEINFO_HPP_
# define GAMEINFO_HPP_

#include <list>
#include "ITCP_protocol.hpp"

class GameInfo
{
private:
	GameInfo();
	~GameInfo();

public:
	void reset();
	static GameInfo &getInstance(void);

public:
	std::list<ITCP_protocol<GameInfo>::Game_stone>	mHisto;
	ITCP_protocol<GameInfo>::Game_stone::Color		mPlate[19][19];
	size_t											mSpecs;
	std::string										mOpponent;
	bool											mGameEnd;
	bool											mConnected;
};

#endif	/* !GAMEINFO_HPP_ */