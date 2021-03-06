#pragma once

#ifndef  GAMEINFO_HPP_
# define GAMEINFO_HPP_

#include	<list>
#include	<vector>
#include	<mutex>
#include	"PlayerInfo.hpp"
#include	"GVOButton.hpp"
#include	"ITCP_protocol.hpp"
#include	"ITCP_client.hpp"

#define		PAGE_GAME_COUNT	(5)

class GameInfo
{
public:
	enum GAMESTATE
	{
		WAITING_PLAYERS,
		RUNNING,
		FINISHED
	};

private:
	GameInfo();
	~GameInfo();
	std::mutex	mMutex;

public:
	void			reset();
	static GameInfo	&getInstance(void);
	void			lock(void);
	void			unlock(void);
	std::mutex		&getMutex(void);

public:
	std::list<iprotocol::Game_stone *>	mHisto;
	iprotocol::Game_stone::Color		mPlate[19][19];
	iprotocol::Game_stone::Color		mWinner;
	size_t								mSpecs;
	std::string							mName;
	std::string							*mBlack;
	std::string							*mWhite;
	std::string							mErrorMessage;
	bool								mShowLobby;
	bool								mShowCreator;
	iprotocol::Game_param				mGameParam;
	GAMESTATE							mGameState;
	PlayerInfo::STATE					mCreate;
	PlayerInfo::STATE					mConnected;
	PlayerInfo::STATE					mDisconnect;
	PlayerInfo::STATE					mUpdateRooms;
	PlayerInfo::STATE					mUpdateTeam;
	PlayerInfo::STATE					mUpdateGameParam;

	int									mRoomPage;
	std::list<GVOButton *>				mGamelist;
	std::vector<iprotocol::Game *>		mRoomlist;
};

#endif	/* !GAMEINFO_HPP_ */