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
#include    "Time.hpp"

Game::Game(typename ITCP_protocol<Client>::Callback &callback, std::string *name) :
    ACallback(callback),
    m_is_start(false),
    m_turn(&m_black),
    m_name(name),
    m_white(*this),
    m_black(*this),
    m_timeout(new Time(5))
{
    m_board.fill(ITCP_protocol<Client>::Game_stone::None);
}

Game::~Game(void)
{
    delete m_timeout;
    delete m_name;
}

void    Game::pre_run(ISelect &iselect)
{
    for (auto *itcp_protocol : m_itcp_protocols)
    {
        Client &client = *itcp_protocol->get_data();

        if (itcp_protocol->want_recv())
            iselect.want_read(*client.get_itcp_client());

        if (itcp_protocol->want_send())
            iselect.want_write(*client.get_itcp_client());
    }
}

void    Game::run(ISelect &iselect, ITime &time)
{
    auto it = m_itcp_protocols.begin();
    while (it != m_itcp_protocols.end())
    {
        auto itcp_protocol = *it;
        Client &client = *itcp_protocol->get_data();

        try
        {
            if (iselect.can_read(*client.get_itcp_client()))
            {
                iselect.reset_read(*client.get_itcp_client());
                itcp_protocol->recv(*client.get_itcp_client());
            }
            else
                timeout(*itcp_protocol);

            if (iselect.can_write(*client.get_itcp_client()))
            {
                iselect.reset_write(*client.get_itcp_client());
                itcp_protocol->send(*client.get_itcp_client());
            }
            it++;
        }
        catch (Game_exception_client_transfer &e)
        {
            e.m_client = itcp_protocol;
            it = m_itcp_protocols.erase(it);
            throw;
        }
        catch (std::exception &e)
        {
            std::cerr << e.what() << std::endl;
            delete itcp_protocol;
            it = m_itcp_protocols.erase(it);
        }
    }
}

void    Game::timeout(ITCP_protocol<Client> &itcp_protocol) const
{
    Client  &client = *itcp_protocol.get_data();
    ITime       &last = *client.get_last();
    intmax_t      second = last.get_second();
    intmax_t      nano = last.get_nano();

    last.now();
    if (last.get_second() - second > m_timeout->get_second()
        || (last.get_second() - second == m_timeout->get_second()
            && last.get_nano() - nano > m_timeout->get_nano()))
    {
        if (client.get_wait_pong() == true)
            throw std::logic_error("timeout");
        client.set_wait_pong(true);
        itcp_protocol.send_ping();
    }
}

void    Game::add_player(ITCP_protocol<Client> *player)
{
    player->set_callback(this);
    m_itcp_protocols.push_back(player);
}

std::list<ITCP_protocol<Client> *> const   &Game::get_players(void) const
{
    return (m_itcp_protocols);
}

std::string const	&Game::get_name(void) const
{
    return (*m_name);
}

void	Game::create_game(ITCP_protocol<Client> &itcp_protocol, typename ITCP_protocol<Client>::Game *game)
{
    delete game->name;
    delete game->owner;
    delete game;
    throw std::logic_error("You are already in game");
}

void	Game::join_game(ITCP_protocol<Client> &itcp_protocol, typename ITCP_protocol<Client>::Game *game)
{
    delete game->name;
    delete game->owner;
    delete game;
    throw std::logic_error("You are already in game");
}

void	Game::leave_game(ITCP_protocol<Client> &itcp_protocol)
{
    throw Game_exception_client_transfer(nullptr);
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

AGame_exception::AGame_exception(void) noexcept
{
}

AGame_exception::AGame_exception(AGame_exception const &) noexcept
{
}

AGame_exception::~AGame_exception(void) noexcept
{
}

AGame_exception     &AGame_exception::operator=(AGame_exception const &) noexcept
{
    return (*this);
}

char const  *AGame_exception::AGame_exception::what(void) const noexcept
{
    return ("AGame_exception");
}

Game_exception_client_transfer::Game_exception_client_transfer(ITCP_protocol<Client> *client) noexcept :
    m_client(client)
{
}

Game_exception_client_transfer::Game_exception_client_transfer(Game_exception_client_transfer const &other) noexcept :
    AGame_exception(),
    m_client(other.m_client)
{
}

Game_exception_client_transfer::~Game_exception_client_transfer(void) noexcept
{
}

Game_exception_client_transfer     &Game_exception_client_transfer::operator=(Game_exception_client_transfer const &) noexcept
{
    return (*this);
}

char const  *Game_exception_client_transfer::Game_exception_client_transfer::what(void) const noexcept
{
    return ("Game_exception_client_transfer");
}
