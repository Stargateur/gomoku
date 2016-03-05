#pragma once

#ifndef PLAYERINFO_HPP__
# define PLAYERINFO_HPP__

#include	<string>
#include	<mutex>
#include	"ITCP_protocol.hpp"
#include	"ITCP_client.hpp"
#include	"GomokuGraphics.hpp"

class PlayerInfo
{
public:
	enum STATE
	{
		NOTHING,
		ASK,
		DOING,
		DONE,
		FAILED
	};

private:
	PlayerInfo();
	~PlayerInfo();
	std::mutex	mMutex;

public:
	static PlayerInfo	&getInstance(void);
	void				lock(void);
	void				unlock(void);
	std::mutex			&getMutex(void);

public:
	GomokuGraphics::e_view					mView;
	float									mMusicVolume;
	std::string								mPseudo;
	std::string								mColor;
	std::string								mHost;
	std::string								mErrorMessage;
	STATE									mQuit;
	STATE									mDisconnect;
	STATE									mConnect;
	STATE									mWantPlay;
	iprotocol::Game_stone	mLastPlay;
};

#endif // !PLAYERINFO_HPP__
