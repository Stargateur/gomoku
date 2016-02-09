//
// Client.cpp for Client in /home/plasko_a/projet/gomoku
//
// Made by Antoine Plaskowski
// Login   <antoine.plaskowski@epitech.eu>
//
// Started on  Wed Jan 27 11:01:51 2016 Antoine Plaskowski
// Last update Wed Jan 27 11:22:59 2016 Antoine Plaskowski
//

#include	<iostream>
#include	"Client.hpp"
#include	"TCP_protocol.hpp"
#include	"TCP_client.hpp"
#include	"Select.hpp"
#include	"PlayerInfo.hpp"
#include	"GameInfo.hpp"
#include	"Time.hpp"

Client::Client(void) :
    m_itcp_protocol(new TCP_protocol<ITCP_client>(this, new TCP_client("localhost", "4242"))),
    m_iselect(new Select)
{
    m_itcp_protocol->send_connect("test", "test");
	ITCP_protocol<ITCP_client>::Game game;
	game.name = new std::string("mdr");
	PlayerInfo::getInstance().lock();
	if (PlayerInfo::getInstance().mColor.compare("black") == 0)
		m_itcp_protocol->send_create_game(game);
	else
		m_itcp_protocol->send_join_game(game);
	ITCP_protocol<ITCP_client>::Game_player_param params;
	params.name = new std::string("color");
	params.value = new std::string(PlayerInfo::getInstance().mColor);
	PlayerInfo::getInstance().unlock();
	m_itcp_protocol->send_change_param_player_game(params);
	m_itcp_protocol->send_ready_game(true);
}

Client::~Client(void)
{
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
        m_iselect->select(Time(0, 500000000));
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

void	Client::result(ITCP_protocol<ITCP_client> &itcp_protocol, typename ITCP_protocol<ITCP_client>::Error error)
{
    std::cout << ITCP_protocol<ITCP_client>::get_str_error(error) << std::endl;
}

void	Client::connect(ITCP_protocol<ITCP_client> &itcp_protocol, uint8_t version, std::string *login, std::string *password)
{
	PlayerInfo::getInstance().lock();
	PlayerInfo::getInstance().mDisconnect = PlayerInfo::STATE::ASK;
	PlayerInfo::getInstance().unlock();
}

void	Client::disconnect(ITCP_protocol<ITCP_client> &itcp_protocol)
{
	PlayerInfo::getInstance().lock();
	PlayerInfo::getInstance().mDisconnect = PlayerInfo::STATE::ASK;
	PlayerInfo::getInstance().unlock();
}

void	Client::ping(ITCP_protocol<ITCP_client> &itcp_protocol)
{
    itcp_protocol.send_pong();
}

void	Client::pong(ITCP_protocol<ITCP_client> &itcp_protocol)
{
}

void	Client::create_game(ITCP_protocol<ITCP_client> &itcp_protocol, typename ITCP_protocol<ITCP_client>::Game *game)
{
}

void	Client::join_game(ITCP_protocol<ITCP_client> &itcp_protocol, typename ITCP_protocol<ITCP_client>::Game *game)
{
}

void	Client::leave_game(ITCP_protocol<ITCP_client> &itcp_protocol)
{
}

void	Client::put_stone_game(ITCP_protocol<ITCP_client> &itcp_protocol, typename ITCP_protocol<ITCP_client>::Game_stone *stone)
{
}

void	Client::change_param_player_game(ITCP_protocol<ITCP_client> &itcp_protocol, typename ITCP_protocol<ITCP_client>::Game_player_param *param)
{
}

void    Client::change_param_game(ITCP_protocol<ITCP_client> &itcp_protocol, typename ITCP_protocol<ITCP_client>::Game_param *param)
{
}

void    Client::list_param_game(ITCP_protocol<ITCP_client> &itcp_protocol, std::list<typename ITCP_protocol<ITCP_client>::Game_param *> *params)
{
}

void    Client::list_param_player_game(ITCP_protocol<ITCP_client> &itcp_protocol, std::list<typename ITCP_protocol<ITCP_client>::Game_player_param *> *params)
{
}

void	Client::game_created(ITCP_protocol<ITCP_client> &itcp_protocol, typename ITCP_protocol<ITCP_client>::Game *game)
{
	mRoomlist.push_back(game);
}

void	Client::game_player_joined(ITCP_protocol<ITCP_client> &itcp_protocol, std::string *name)
{
}

void	Client::game_player_left(ITCP_protocol<ITCP_client> &itcp_protocol, std::string *name)
{
}

void    Client::game_player_param_changed(ITCP_protocol<ITCP_client> &itcp_protocol, typename ITCP_protocol<ITCP_client>::Game_player_param *param)
{
}

void	Client::game_param_changed(ITCP_protocol<ITCP_client> &itcp_protocol, typename ITCP_protocol<ITCP_client>::Game_param *param)
{
}

void	Client::game_stone_put(ITCP_protocol<ITCP_client> &itcp_protocol, typename ITCP_protocol<ITCP_client>::Game_stone *stone)
{
	GameInfo::getInstance().lock();
	if (stone != nullptr)
	{
		GameInfo::getInstance().mPlate[stone->x][stone->y] = stone->color;
		GameInfo::getInstance().mHisto.push_back(stone);
	}
	GameInfo::getInstance().unlock();
}

void	Client::game_deleted(ITCP_protocol<ITCP_client> &itcp_protocol, typename ITCP_protocol<ITCP_client>::Game *game)
{
	mRoomlist.remove(game);
}

void	Client::start_game(ITCP_protocol<ITCP_client> &itcp_protocol)
{
}

void	Client::ready_game(ITCP_protocol<ITCP_client> &itcp_protocol, bool ready)
{
}

void	Client::result_game(ITCP_protocol<ITCP_client> &itcp_protocol, typename ITCP_protocol<ITCP_client>::Game_result *game_result)
{
	PlayerInfo::getInstance().lock();
	PlayerInfo::getInstance().mDisconnect = PlayerInfo::STATE::ASK;
	PlayerInfo::getInstance().unlock();
}

void	Client::message(ITCP_protocol<ITCP_client> &itcp_protocol, typename ITCP_protocol<ITCP_client>::Message *message)
{
}

void Client::checkUserInputs(void)
{
	PlayerInfo::getInstance().lock();
	std::cout << "checking user" << std::endl;
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
		m_itcp_protocol->send_put_stone_game(PlayerInfo::getInstance().mLastPlay);
		PlayerInfo::getInstance().mWantPlay = PlayerInfo::STATE::DONE;
	}
	PlayerInfo::getInstance().unlock();
}
