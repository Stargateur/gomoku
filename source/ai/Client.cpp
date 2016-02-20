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
#include	"Time.hpp"

Client::Client(void) :
    m_itcp_protocol(new iprotocol::TCP_protocol<ITCP_client>(this, new TCP_client("localhost", "4242"))),
    m_iselect(new Select)
{
    m_itcp_protocol->send_connect("ia", "ia");
	iprotocol::Game game;
	game.name = new std::string("mdr");
	m_itcp_protocol->send_join_game(game);
	iprotocol::Game_player_param params;
	params.name = new std::string("color");
	params.value = new std::string("white");
	m_itcp_protocol->send_change_param_player_game(params);
	m_itcp_protocol->send_ready_game(true);
}

Client::~Client(void)
{
}

void	Client::pre_run(void)
{
	m_iselect->reset();
	if (m_itcp_protocol->want_recv() == true)
		m_iselect->want_read(*m_itcp_protocol->get_data());
	if (m_itcp_protocol->want_send() == true)
		m_iselect->want_write(*m_itcp_protocol->get_data());
}

void	Client::run(void)
{
    m_iselect->select();
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
}

void	Client::result(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol, iprotocol::Error error)
{
    std::cout << error << std::endl;
}

void	Client::connect(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol, uint8_t version, std::string *login, std::string *password)
{
}

void	Client::disconnect(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol)
{
}

void	Client::ping(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol)
{
    itcp_protocol.send_pong();
}

void	Client::pong(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol)
{
}

void	Client::create_game(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol, typename iprotocol::Game *game)
{
}

void	Client::join_game(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol, typename iprotocol::Game *game)
{
}

void	Client::leave_game(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol)
{
}

void	Client::put_stone_game(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol, typename iprotocol::Game_stone *stone)
{
}

void	Client::change_param_player_game(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol, typename iprotocol::Game_player_param *param)
{
}

void    Client::change_param_game(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol, typename iprotocol::Game_param *param)
{
}

void    Client::list_param_game(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol, std::list<typename iprotocol::Game_param *> *params)
{
}

void    Client::list_param_player_game(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol, std::list<typename iprotocol::Game_player_param *> *params)
{
}

void	Client::game_created(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol, typename iprotocol::Game *game)
{
	mRoomlist.push_back(game);
}

void	Client::game_player_joined(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol, std::string *name)
{
}

void	Client::game_player_left(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol, std::string *name)
{
}

void    Client::game_player_param_changed(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol, typename iprotocol::Game_player_param *param)
{
}

void	Client::game_param_changed(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol, typename iprotocol::Game_param *param)
{
}

void	Client::game_stone_put(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol, typename iprotocol::Game_stone *stone)
{
	stone->color = iprotocol::Game_stone::White;
	stone->x--;
	stone->y--;
	itcp_protocol.send_put_stone_game(*stone);
}

void	Client::game_deleted(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol, typename iprotocol::Game *game)
{
	mRoomlist.remove(game);
}

void	Client::start_game(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol)
{
}

void	Client::ready_game(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol, bool ready)
{
}

void	Client::result_game(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol, typename iprotocol::Game_result *game_result)
{
}

void	Client::message(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol, typename iprotocol::Message *message)
{
}
