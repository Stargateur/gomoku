#include	<string>
#include	<SFML/Graphics.hpp>
#include	"GomokuGraphics.hpp"
#include	"GameInfo.hpp"
#include	"PlayerInfo.hpp"
#include	"GomokuGraphicsHandler.hpp"

void		connect(int u)
{
	PlayerInfo::getInstance().lock();
	if (true)
	{
		std::cout << "Asking connection" << std::endl;
		PlayerInfo::getInstance().mConnect = PlayerInfo::STATE::ASK;
	}
	PlayerInfo::getInstance().unlock();
}

void		connect_room(std::string room)
{
	GameInfo::getInstance().lock();
	if (GameInfo::getInstance().mConnected == PlayerInfo::STATE::NOTHING || GameInfo::getInstance().mConnected == PlayerInfo::STATE::FAILED)
	{
		std::cout << "connecting to " << room << "..." << std::endl;
		GameInfo::getInstance().mName = room;
		GameInfo::getInstance().mConnected = PlayerInfo::STATE::ASK;
	}
	GameInfo::getInstance().unlock();
}

void		click_plateau(sf::Vector2f *param)
{
	size_t		xStart = 242;
	size_t		yStart = 98;
	size_t		prec = 10;
	bool		canPlay = false;

	GameInfo::getInstance().lock();
	canPlay = GameInfo::getInstance().mGameState == GameInfo::GAMESTATE::RUNNING;
	GameInfo::getInstance().unlock();
	if (param != NULL && canPlay)
	{
		for (size_t x = 0; x < 19; x++)
		{
			for (size_t y = 0; y < 19; y++)
			{
				float tryX = xStart + x * 33.5;
				float tryY = yStart + y * 33.5;
				if ((param->x <= tryX + 10 && param->x >= tryX - 10) &&
					(param->y <= tryY + 10 && param->y >= tryY - 10))
				{
					PlayerInfo::getInstance().lock();
					PlayerInfo::getInstance().mLastPlay.x = x;
					PlayerInfo::getInstance().mLastPlay.y = y;
					if (PlayerInfo::getInstance().mColor.compare("black") == 0)
						PlayerInfo::getInstance().mLastPlay.color = PlayerInfo::getInstance().mLastPlay.Black;
					else
						PlayerInfo::getInstance().mLastPlay.color = PlayerInfo::getInstance().mLastPlay.White;
					PlayerInfo::getInstance().mWantPlay = PlayerInfo::STATE::ASK;
					PlayerInfo::getInstance().unlock();
				}
			}
		}
	}
}

void		change_color(std::string color)
{
	PlayerInfo::getInstance().lock();
	PlayerInfo::getInstance().mColor = color;
	PlayerInfo::getInstance().unlock();
}

void		change_view(GomokuGraphics::e_view view)
{
	PlayerInfo::getInstance().lock();
	PlayerInfo::getInstance().mView = view;
	PlayerInfo::getInstance().unlock();
}

void		validate_team(int use)
{
	GameInfo::getInstance().lock();
	GameInfo::getInstance().mShowLobby = false;
	GameInfo::getInstance().mUpdateTeam = PlayerInfo::STATE::ASK;
	GameInfo::getInstance().unlock();
}

void		mute_speaker(int volume)
{
	PlayerInfo::getInstance().lock();
	PlayerInfo::getInstance().mMusicMute = !PlayerInfo::getInstance().mMusicMute;
	PlayerInfo::getInstance().unlock();
}

void		change_volume(float volume)
{
	PlayerInfo::getInstance().lock();
	PlayerInfo::getInstance().mMusicVolume += volume;
	if (PlayerInfo::getInstance().mMusicVolume < 0)
		PlayerInfo::getInstance().mMusicVolume = 0;
	else if (PlayerInfo::getInstance().mMusicVolume > 100)
		PlayerInfo::getInstance().mMusicVolume = 100;
	PlayerInfo::getInstance().mStringVolume = std::to_string(static_cast<int>(PlayerInfo::getInstance().mMusicVolume));
	PlayerInfo::getInstance().unlock();
}

void		create_game(PlayerInfo::STATE state)
{
	GameInfo::getInstance().lock();
	if (GameInfo::getInstance().mCreate != PlayerInfo::STATE::DOING || GameInfo::getInstance().mCreate != PlayerInfo::STATE::ASK)
	{
		GameInfo::getInstance().mConnected = PlayerInfo::STATE::DOING;
		GameInfo::getInstance().mCreate = state;
	}
	GameInfo::getInstance().unlock();
}

void change_gamepage(int modifier)
{
	std::cout << "Changing page" << std::endl;
	GameInfo::getInstance().lock();
	GameInfo::getInstance().mRoomPage += modifier;
	if (GameInfo::getInstance().mRoomPage < 1)
		GameInfo::getInstance().mRoomPage = 1;
	GameInfo::getInstance().mUpdateRooms = PlayerInfo::STATE::ASK;
	std::cout << "Page changed to " << GameInfo::getInstance().mRoomPage << " !" << std::endl;
	GameInfo::getInstance().unlock();
}
void quit_game(int use)
{
	GameInfo::getInstance().lock();
	GameInfo::getInstance().mDisconnect = PlayerInfo::STATE::ASK;
	GameInfo::getInstance().unlock();
}

void toggle_gameparam(int paramid)
{
	GameInfo::getInstance().lock();
	switch (paramid)
	{
	case 0:
		GameInfo::getInstance().mGameParam.five_breakable = !GameInfo::getInstance().mGameParam.five_breakable;
		break;
	case 1:
		GameInfo::getInstance().mGameParam.three_and_three = !GameInfo::getInstance().mGameParam.three_and_three;
		break;
	case 2:
		GameInfo::getInstance().mGameParam.ai_black = !GameInfo::getInstance().mGameParam.ai_black;
		GameInfo::getInstance().mGameParam.ai_white = false;
		break;
	case 3:
		GameInfo::getInstance().mGameParam.ai_black = false;
		GameInfo::getInstance().mGameParam.ai_white = !GameInfo::getInstance().mGameParam.ai_white;
		break;
	};
	GameInfo::getInstance().unlock();
}

void validate_gameparam(int use)
{
	GameInfo::getInstance().lock();
	GameInfo::getInstance().mUpdateGameParam = PlayerInfo::STATE::ASK;
	GameInfo::getInstance().unlock();
}
