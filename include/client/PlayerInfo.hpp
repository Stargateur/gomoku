#pragma once

#ifndef PLAYERINFO_HPP__
# define PLAYERINFO_HPP__

#include <string>
#include "ITCP_protocol.hpp"

class PlayerInfo
{
private:
	PlayerInfo();
	~PlayerInfo();

public:
	static PlayerInfo &getInstance(void);

public:
	std::string								mPseudo;
	std::string								mHost;
	bool									mWantQuit;
	bool									mWantDisconnect;
	bool									mWantConnect;
	bool									mWantPlay;
	ITCP_protocol<PlayerInfo>::Game_stone	mLastPlay;
};

#endif // !PLAYERINFO_HPP__
