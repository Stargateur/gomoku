#include	<iostream>
#include	"Client.hpp"
#include	"TCP_protocol.hpp"
#include	"TCP_client.hpp"
#include	"Select.hpp"
#include	"PlayerInfo.hpp"
#include	"GameInfo.hpp"

Client::Client(std::string const &host) :
    m_itcp_protocol(new iprotocol::TCP_protocol<ITCP_client>(this, new TCP_client(host, "4242"))),
    m_iselect(new Select)
{
	PlayerInfo::getInstance().lock();
	m_itcp_protocol->send_connect(PlayerInfo::getInstance().mPseudo, PlayerInfo::getInstance().mPseudo);
	iprotocol::Game game;
	game.name = new std::string("mdr");
	if (PlayerInfo::getInstance().mColor.compare("black") == 0)
		m_itcp_protocol->send_game_create(game);
	else
		m_itcp_protocol->send_game_join(game);
	iprotocol::Game_player_param param;
    std::string lol("test");
    param.name = &lol;
    if (PlayerInfo::getInstance().mColor == "black")
        param.type = iprotocol::Game_player_param::Black;
    else
        param.type = iprotocol::Game_player_param::White;        
	PlayerInfo::getInstance().unlock();
	m_itcp_protocol->send_game_player_param(param);
	m_itcp_protocol->send_game_ready(true);
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
    mRoomlist.push_back(game);
}

void    Client::game_delete(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol, typename iprotocol::Game *game)
{
}

void	Client::game_join(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol, typename iprotocol::Game *game)
{
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
	PlayerInfo::getInstance().lock();
	PlayerInfo::getInstance().mDisconnect = PlayerInfo::STATE::ASK;
	PlayerInfo::getInstance().unlock();
}

void	Client::game_message(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol, typename iprotocol::Message *message)
{
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
}
