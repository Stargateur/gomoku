//
// Game.cpp for Game in /home/plasko_a/projet/gomoku
//
// Made by Antoine Plaskowski
// Login   <antoine.plaskowski@epitech.eu>
//
// Started on  Wed Jan 27 15:21:28 2016 Antoine Plaskowski
// Last update Thu Jan 28 10:46:40 2016 Antoine Plaskowski
//

#include    <iostream>
#include    "Game.hpp"
#include    "Server.hpp"

Game::Game(typename ITCP_protocol<Client>::Callback &callback, std::string *name) :
    ACallback(callback),
    m_is_start(false),
    m_turn(&m_black),
    m_name(name),
    m_white(*this),
    m_black(*this)
{
    m_board.fill(ITCP_protocol<Client>::Game_stone::None);
}

Game::~Game(void)
{
    delete m_name;
}

std::string const	&Game::get_name(void) const
{
    return (*m_name);
}

void	Game::create_game(ITCP_protocol<Client> &itcp_protocol, typename ITCP_protocol<Client>::Game *game)
{
    throw std::logic_error("You are already in game");
}

void	Game::join_game(ITCP_protocol<Client> &itcp_protocol, typename ITCP_protocol<Client>::Game *game)
{
    throw std::logic_error("You are already in game");
}

void	Game::leave_game(ITCP_protocol<Client> &itcp_protocol)
{
    std::cout << "laixickdk" << std::endl;
    throw Server_exception_client_transfer(this);
}

void	Game::put_stone_game(ITCP_protocol<Client> &itcp_protocol, typename ITCP_protocol<Client>::Game_stone *stone)
{
    if (m_is_start == false)
        ;
    if (stone->x >= m_size || stone->y >= m_size)
        ;
    if (m_board[stone->y * m_size + stone->x] != ITCP_protocol<Client>::Game_stone::None)
        ;
    if (m_turn != itcp_protocol.get_callback())
        ;
    m_board[stone->y * m_size + stone->x] = stone->color;
    throw std::logic_error("Satan is here");
    for (auto it : m_itcp_protocols)
        it->send_game_stone_put(*stone);
}

void	Game::change_param_game(ITCP_protocol<Client> &itcp_protocol, typename ITCP_protocol<Client>::Game_param *param)
{
}

void	Game::list_param_game(ITCP_protocol<Client> &itcp_protocol, std::list<typename ITCP_protocol<Client>::Game_param *> *params)
{
}

void	Game::start_game(ITCP_protocol<Client> &itcp_protocol)
{
    if (m_white.is_ready() == false || m_black.is_ready() == false)
        ;
    else
        m_is_start = true;
}

void	Game::ready_game(ITCP_protocol<Client> &itcp_protocol, bool ready)
{
    throw std::logic_error("Impossible has happen");
}
