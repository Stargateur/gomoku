//
// White.cpp for White in /home/plasko_a/projet/gomoku
//
// Made by Antoine Plaskowski
// Login   <antoine.plaskowski@epitech.eu>
//
// Started on  Wed Jan 27 15:21:28 2016 Antoine Plaskowski
// Last update Thu Jan 28 10:26:09 2016 Antoine Plaskowski
//

#include	"White.hpp"

White::White(typename ITCP_protocol<Client>::Callback &callback) :
    ACallback(callback),
    m_is_ready(false)
{
}

White::~White(void)
{
}

bool	White::is_ready(void) const
{
    return (m_is_ready);
}

void	White::put_stone_game(ITCP_protocol<Client> &itcp_protocol, typename ITCP_protocol<Client>::Game_stone *stone)
{
    stone->color = ITCP_protocol<Client>::Game_stone::Color::White;
    m_callback.put_stone_game(itcp_protocol, stone);
}

void	White::ready_game(ITCP_protocol<Client> &, bool ready)
{
    m_is_ready = ready;
}
