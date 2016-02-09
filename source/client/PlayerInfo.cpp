#include "PlayerInfo.hpp"

PlayerInfo::PlayerInfo() : mWantQuit(false), mWantDisconnect(false), mWantConnect(false), mWantPlay(false), mIsConnected(false)
{
}

PlayerInfo::~PlayerInfo()
{
}

PlayerInfo & PlayerInfo::getInstance(void)
{
	static PlayerInfo instance;
	return instance;
}

void PlayerInfo::lock(void)
{
	mMutex.lock();
}

void PlayerInfo::unlock(void)
{
	mMutex.unlock();
}
