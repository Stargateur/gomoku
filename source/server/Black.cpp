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

Black::Black(typename ITCP_protocol<Client>::Callback &callback) :
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

void	Black::put_stone_game(ITCP_protocol<Client> &itcp_protocol, typename ITCP_protocol<Client>::Game_stone *stone)
{
  if (stone->color != ITCP_protocol<Client>::Game_stone::Color::Black)
    throw std::logic_error("place que du black");
  m_callback.put_stone_game(itcp_protocol, stone);
}

void	Black::ready_game(ITCP_protocol<Client> &itcp_protocol, bool ready)
{
  m_is_ready = ready;
}
