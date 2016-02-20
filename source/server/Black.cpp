//
// Black.cpp for Black in /home/plasko_a/projet/gomoku
//
// Made by Antoine Plaskowski
// Login   <antoine.plaskowski@epitech.eu>
//
// Started on  Wed Jan 27 15:21:28 2016 Antoine Plaskowski
// Last update Thu Jan 28 10:25:25 2016 Antoine Plaskowski
//

#include	"Black.hpp"

Black::Black(typename iprotocol::ITCP_protocol<Client>::Callback &callback) :
    ACallback(callback),
    m_is_ready(false)
{
}

Black::~Black(void)
{
}

bool	Black::is_ready(void) const
{
    return (m_is_ready);
}

void	Black::put_stone_game(iprotocol::ITCP_protocol<Client> &itcp_protocol, iprotocol::Game_stone *stone)
{
    stone->color = iprotocol::Game_stone::Color::Black;
    m_callback.put_stone_game(itcp_protocol, stone);
}

void	Black::ready_game(iprotocol::ITCP_protocol<Client> &, bool ready)
{
    m_is_ready = ready;
}
