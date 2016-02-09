#pragma once

#ifndef PLAYERINFO_HPP__
# define PLAYERINFO_HPP__

#include	<string>
#include	<mutex>
#include	"ITCP_protocol.hpp"
#include	"ITCP_client.hpp"

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
	std::string								mColor;
	std::string								mHost;
	std::string								mErrorMessage;
	bool									mWantQuit;
	bool									mWantDisconnect;
	bool									mWantConnect;
	bool									mWantPlay;
	bool									mHasFailed;
	bool									mIsConnected;
	ITCP_protocol<ITCP_client>::Game_stone	mLastPlay;
};

#endif // !PLAYERINFO_HPP__
