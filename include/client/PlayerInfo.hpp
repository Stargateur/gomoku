#pragma once

#ifndef PLAYERINFO_HPP__
# define PLAYERINFO_HPP__

#include <string>
#include <mutex>
#include "ITCP_protocol.hpp"

class PlayerInfo
{
private:
	PlayerInfo();
	~PlayerInfo();
	std::mutex	mMutex;

public:
	static PlayerInfo	&getInstance(void);
	void				lock(void);
	void				unlock(void);

public:
	std::string								mPseudo;
	std::string								mHost;
	std::string								mErrorMessage;
	bool									mWantQuit;
	bool									mWantDisconnect;
	bool									mWantConnect;
	bool									mWantPlay;
	bool									mHasFailed;
	bool									mIsConnected;
	ITCP_protocol<PlayerInfo>::Game_stone	mLastPlay;
};

#endif // !PLAYERINFO_HPP__
