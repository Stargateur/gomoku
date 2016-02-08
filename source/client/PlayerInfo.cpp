#include "PlayerInfo.hpp"

PlayerInfo::PlayerInfo() : mWantQuit(false), mWantDisconnect(false), mWantConnect(false), mWantPlay(false)
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
