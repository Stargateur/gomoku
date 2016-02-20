#pragma once

#ifndef  GAMEINFO_HPP_
# define GAMEINFO_HPP_

#include	<list>
#include	<mutex>
#include	"ITCP_protocol.hpp"
#include	"ITCP_client.hpp"

class GameInfo
{
private:
	GameInfo();
	~GameInfo();
	std::mutex	mMutex;

public:
	void			reset();
	static GameInfo	&getInstance(void);
	void			lock(void);
	void			unlock(void);

public:
	std::list<iprotocol::ITCP_protocol<ITCP_client>::Game_stone *>	mHisto;
	iprotocol::ITCP_protocol<ITCP_client>::Game_stone::Color		mPlate[19][19];
	size_t											mSpecs;
	std::string										mOpponent;
	bool											mGameEnd;
	bool											mConnected;
};

#endif	/* !GAMEINFO_HPP_ */