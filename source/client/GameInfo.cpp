#include "GameInfo.hpp"

GameInfo::GameInfo() : mBlack(nullptr), mWhite(nullptr)
{
	reset();
}

GameInfo::~GameInfo()
{
}

void GameInfo::reset()
{
	mHisto.clear();
	for (int x = 0; x < 19; x++)
		for (int y = 0; y < 19; y++)
			mPlate[x][y] = iprotocol::Game_stone::Color::None;
	mSpecs = 0;
	if (mBlack != nullptr)
		delete mBlack;
	mBlack = nullptr;
	if (mWhite != nullptr)
		delete mBlack;
	mWhite = nullptr;
	mName = "";
	mGameState = GAMESTATE::WAITING_PLAYERS;
	mShowLobby = true;
	mConnected = PlayerInfo::STATE::NOTHING;
	mDisconnect = PlayerInfo::STATE::NOTHING;
	mUpdateRooms = PlayerInfo::STATE::NOTHING;
	mCreate = PlayerInfo::STATE::NOTHING;
	mUpdateTeam = PlayerInfo::STATE::NOTHING;
	mRoomPage = 1;
}

GameInfo & GameInfo::getInstance(void)
{
	static GameInfo instance;
	return instance;
}

void GameInfo::lock(void)
{
	mMutex.lock();
}

void GameInfo::unlock(void)
{
	mMutex.unlock();
}

std::mutex & GameInfo::getMutex(void)
{
	return mMutex;
}
