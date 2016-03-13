#include	<iostream>
#include	"Client.hpp"
#include	"ITCP_protocol.hpp"
#include	"TCP_protocol.hpp"
#include	"TCP_client.hpp"
#include	"Select.hpp"
#include	"PlayerInfo.hpp"
#include	"GameInfo.hpp"

Client::Client(std::string const &host, std::string const &port) :
    m_itcp_protocol(new iprotocol::TCP_protocol<ITCP_client>(this, new TCP_client(host, port))),
    m_iselect(new Select)
{
	PlayerInfo::getInstance().lock();
	m_itcp_protocol->send_connect(PlayerInfo::getInstance().mPseudo, PlayerInfo::getInstance().mPseudo);
	PlayerInfo::getInstance().unlock();
}

Client::~Client(void)
{
    delete m_itcp_protocol;
    delete m_iselect;
}

void	Client::run(void)
{
    bool	g_keep_running = true;

    while (g_keep_running == true)
    {
        m_iselect->reset();
        if (m_itcp_protocol->want_recv() == true)
            m_iselect->want_read(*m_itcp_protocol->get_data());
        if (m_itcp_protocol->want_send() == true)
            m_iselect->want_write(*m_itcp_protocol->get_data());
        m_iselect->select(std::chrono::nanoseconds(500000000));
        if (m_iselect->can_read(*m_itcp_protocol->get_data()) == true)
		{
			m_iselect->reset_read(*m_itcp_protocol->get_data());
            m_itcp_protocol->recv(*m_itcp_protocol->get_data());
		}
        if (m_iselect->can_write(*m_itcp_protocol->get_data()) == true)
		{
			m_iselect->reset_write(*m_itcp_protocol->get_data());
            m_itcp_protocol->send(*m_itcp_protocol->get_data());
		}
		checkUserInputs();
		PlayerInfo::getInstance().lock();
		g_keep_running = PlayerInfo::getInstance().mDisconnect != PlayerInfo::STATE::DONE;
		PlayerInfo::getInstance().unlock();
    }
}

void	Client::result(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol, iprotocol::Error error)
{
	switch (error)
	{
	case (iprotocol::Error::Not_connected):
		GameInfo::getInstance().lock();
		GameInfo::getInstance().mConnected = PlayerInfo::STATE::FAILED;
		GameInfo::getInstance().mErrorMessage = "Impossible de se connecter au serveur !";
		GameInfo::getInstance().unlock();
		break;
	case (iprotocol::Error::Already_in_game):
		GameInfo::getInstance().lock();
		GameInfo::getInstance().mConnected = PlayerInfo::STATE::FAILED;
		GameInfo::getInstance().mErrorMessage = "Vous êtes déjà dans une partie !";
		GameInfo::getInstance().unlock();
		break;
	default:
		break;
	}
    std::cout << error << std::endl;
}

void	Client::connect(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol, uint8_t version, std::string *login, std::string *password)
{
	PlayerInfo::getInstance().lock();
	PlayerInfo::getInstance().mDisconnect = PlayerInfo::STATE::ASK;
	PlayerInfo::getInstance().unlock();
}

void	Client::disconnect(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol)
{
	PlayerInfo::getInstance().lock();
	PlayerInfo::getInstance().mDisconnect = PlayerInfo::STATE::ASK;
	PlayerInfo::getInstance().unlock();
}

void	Client::ping(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol)
{
    itcp_protocol.send_pong();
}

void	Client::pong(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol)
{
}

void	Client::game_create(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol, typename iprotocol::Game *game)
{
	GameInfo::getInstance().lock();
    GameInfo::getInstance().mRoomlist.push_back(game);
	GameInfo::getInstance().mUpdateRooms = PlayerInfo::STATE::ASK;
	if (GameInfo::getInstance().mCreate == PlayerInfo::STATE::DOING && GameInfo::getInstance().mName == *game->name)
	{
		GameInfo::getInstance().mCreate = PlayerInfo::STATE::DONE;
		GameInfo::getInstance().mShowCreator = true;
	}
	GameInfo::getInstance().unlock();
}

void    Client::game_delete(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol, typename iprotocol::Game *game)
{
	GameInfo::getInstance().lock();
	std::cout << "GAME DELETED : " << *game->name << std::endl;
	std::vector<iprotocol::Game *>::const_iterator it = GameInfo::getInstance().mRoomlist.begin();
	while (it != GameInfo::getInstance().mRoomlist.end() && *(*it)->name != *(game->name))
		it++;
	if (it != GameInfo::getInstance().mRoomlist.end())
		GameInfo::getInstance().mRoomlist.erase(it);
	GameInfo::getInstance().mUpdateRooms = PlayerInfo::STATE::ASK;
	GameInfo::getInstance().unlock();
}

void	Client::game_join(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol, typename iprotocol::Game *game)
{
	std::cout << "TU AS REJOINDS LA GAME" << std::endl;
	GameInfo::getInstance().lock();
	GameInfo::getInstance().mConnected = PlayerInfo::STATE::DONE;
	GameInfo::getInstance().unlock();
}

void	Client::game_leave(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol)
{
}

void	Client::game_stone_put(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol, typename iprotocol::Game_stone *stone)
{
    GameInfo::getInstance().lock();
    if (stone != nullptr)
    {
        GameInfo::getInstance().mPlate[stone->x][stone->y] = stone->color;
        GameInfo::getInstance().mHisto.push_back(stone);
    }
    GameInfo::getInstance().unlock();
}

void	Client::game_player_param(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol, typename iprotocol::Game_player_param *param)
{
}

void    Client::game_param(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol, typename iprotocol::Game_param *param)
{
}

void	Client::game_player_join(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol, std::string *name)
{
}

void	Client::game_player_leave(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol, std::string *name)
{
}

void	Client::game_start(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol)
{
	GameInfo::getInstance().lock();
	GameInfo::getInstance().mGameState = GameInfo::GAMESTATE::RUNNING;
	GameInfo::getInstance().unlock();
}

void	Client::game_ready(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol, bool ready)
{
}

void    Client::game_score(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol, typename iprotocol::Game_score *game_score)
{
}

void    Client::game_help(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol)
{
}

void    Client::game_hint(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol, typename iprotocol::Game_stone *stone)
{
}

void	Client::game_result(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol, typename iprotocol::Game_result *game_result)
{
	GameInfo::getInstance().lock();
	if (game_result->winner == iprotocol::Game_result::Color::Black)
		GameInfo::getInstance().mWinner = iprotocol::Game_stone::Color::Black;
	else
		GameInfo::getInstance().mWinner = iprotocol::Game_stone::Color::White;
	GameInfo::getInstance().mGameState = GameInfo::GAMESTATE::FINISHED;
	GameInfo::getInstance().unlock();
}

void	Client::game_message(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol, typename iprotocol::Message *message)
{
	std::cout << "message (" << *message->name << "): " << *message->message << std::endl;
}

void Client::checkUserInputs(void)
{
	PlayerInfo::getInstance().lock();
	if (PlayerInfo::getInstance().mDisconnect == PlayerInfo::STATE::ASK)
	{
		m_itcp_protocol->send_disconnect();
		PlayerInfo::getInstance().mDisconnect = PlayerInfo::STATE::DONE;
	}
	else if (PlayerInfo::getInstance().mQuit == PlayerInfo::STATE::ASK)
	{
		m_itcp_protocol->send_disconnect();
		PlayerInfo::getInstance().mQuit = PlayerInfo::STATE::DONE;
		PlayerInfo::getInstance().mDisconnect = PlayerInfo::STATE::DONE;
	}
	if (PlayerInfo::getInstance().mWantPlay == PlayerInfo::STATE::ASK)
	{
		m_itcp_protocol->send_game_stone_put(PlayerInfo::getInstance().mLastPlay);
		PlayerInfo::getInstance().mWantPlay = PlayerInfo::STATE::DONE;
	}
	PlayerInfo::getInstance().unlock();
	GameInfo::getInstance().lock();
	if (GameInfo::getInstance().mConnected == PlayerInfo::STATE::ASK)
	{
		GameInfo::getInstance().mConnected = PlayerInfo::STATE::DOING;
		iprotocol::Game game;
		game.name = new std::string(GameInfo::getInstance().mName);
		m_itcp_protocol->send_game_join(game);
	}
	else if (GameInfo::getInstance().mCreate == PlayerInfo::STATE::ASK)
	{
		GameInfo::getInstance().mCreate = PlayerInfo::STATE::DOING;
		iprotocol::Game game;
		game.name = new std::string(GameInfo::getInstance().mName);
		m_itcp_protocol->send_game_create(game);
	}
	if (GameInfo::getInstance().mConnected == PlayerInfo::STATE::DONE && GameInfo::getInstance().mUpdateTeam == PlayerInfo::STATE::ASK)
	{
		GameInfo::getInstance().mUpdateTeam = PlayerInfo::STATE::DONE;
		iprotocol::Game_player_param param;
		std::string lol("test");
		param.name = &lol;
		if (PlayerInfo::getInstance().mColor == "black")
			param.type = iprotocol::Game_player_param::Black;
		else
			param.type = iprotocol::Game_player_param::White;
		m_itcp_protocol->send_game_player_param(param);
		m_itcp_protocol->send_game_ready(true);
		GameInfo::getInstance().mGameState = GameInfo::GAMESTATE::RUNNING;
		GameInfo::getInstance().mUpdateTeam = PlayerInfo::STATE::DONE;
	}
	if (GameInfo::getInstance().mConnected == PlayerInfo::STATE::DONE && GameInfo::getInstance().mUpdateGameParam == PlayerInfo::STATE::ASK)
	{
		GameInfo::getInstance().mUpdateGameParam = PlayerInfo::STATE::DONE;
		m_itcp_protocol->send_game_param(GameInfo::getInstance().mGameParam);
		GameInfo::getInstance().mShowCreator = false;
	}
	if (GameInfo::getInstance().mDisconnect == PlayerInfo::STATE::ASK && GameInfo::getInstance().mConnected == PlayerInfo::STATE::DONE)
	{
		m_itcp_protocol->send_game_leave();
		GameInfo::getInstance().mShowLobby = true;
		GameInfo::getInstance().mDisconnect = PlayerInfo::STATE::DONE;
		GameInfo::getInstance().mConnected = PlayerInfo::STATE::NOTHING;
		GameInfo::getInstance().mUpdateRooms = PlayerInfo::STATE::ASK;
		m_itcp_protocol->send_ping();
	}
	GameInfo::getInstance().unlock();
}
