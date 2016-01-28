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

Client::Client(void) :
    m_itcp_protocol(new TCP_protocol<ITCP_client>(this, new TCP_client("localhost", "4242"))),
    m_iselect(new Select)
{
    m_itcp_protocol->send_connect("plasko_a", "plasko_a");
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
        m_iselect->select();
        if (m_iselect->can_read(*m_itcp_protocol->get_data()) == true)
            m_itcp_protocol->recv(*m_itcp_protocol->get_data());
        if (m_iselect->can_write(*m_itcp_protocol->get_data()) == true)
            m_itcp_protocol->send(*m_itcp_protocol->get_data());
    }
}

void	Client::result(ITCP_protocol<ITCP_client> &itcp_protocol, typename ITCP_protocol<ITCP_client>::Error error)
{
    std::cout << error << std::endl;
}

void	Client::connect(ITCP_protocol<ITCP_client> &itcp_protocol, uint8_t version, std::string *login, std::string *password)
{
}

void	Client::disconnect(ITCP_protocol<ITCP_client> &itcp_protocol)
{
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

void	Client::change_param_game(ITCP_protocol<ITCP_client> &itcp_protocol, typename ITCP_protocol<ITCP_client>::Game_param *param)
{
}

void	Client::list_param_game(ITCP_protocol<ITCP_client> &itcp_protocol, std::list<typename ITCP_protocol<ITCP_client>::Game_param *> *params)
{
}

void	Client::game_created(ITCP_protocol<ITCP_client> &itcp_protocol, typename ITCP_protocol<ITCP_client>::Game *game)
{
}

void	Client::game_player_joined(ITCP_protocol<ITCP_client> &itcp_protocol, std::string *name)
{
}

void	Client::game_player_left(ITCP_protocol<ITCP_client> &itcp_protocol, std::string *name)
{
}

void	Client::game_param_changed(ITCP_protocol<ITCP_client> &itcp_protocol, typename ITCP_protocol<ITCP_client>::Game_param *param)
{
}

void	Client::game_stone_put(ITCP_protocol<ITCP_client> &itcp_protocol, typename ITCP_protocol<ITCP_client>::Game_stone *stone)
{
}

void	Client::game_deleted(ITCP_protocol<ITCP_client> &itcp_protocol, typename ITCP_protocol<ITCP_client>::Game *game)
{
}

void	Client::start_game(ITCP_protocol<ITCP_client> &itcp_protocol)
{
}

void	Client::ready_game(ITCP_protocol<ITCP_client> &itcp_protocol, bool ready)
{
}

void	Client::result_game(ITCP_protocol<ITCP_client> &itcp_protocol, typename ITCP_protocol<ITCP_client>::Game_result *game_result)
{
}

void	Client::message(ITCP_protocol<ITCP_client> &itcp_protocol, typename ITCP_protocol<ITCP_client>::Message *message)
{
}
