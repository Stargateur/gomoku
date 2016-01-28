//
// Game.cpp for Game in /home/plasko_a/projet/gomoku
// 
// Made by Antoine Plaskowski
// Login   <antoine.plaskowski@epitech.eu>
// 
// Started on  Wed Jan 27 15:21:28 2016 Antoine Plaskowski
// Last update Thu Jan 28 10:28:15 2016 Antoine Plaskowski
//

#include	"Game.hpp"

Game::Game(typename ITCP_protocol<Client>::Callback &callback, std::string *name) :
  ACallback(callback),
  m_is_start(false),
  m_white_is_ready(false),
  m_black_is_ready(false),
  m_turn(ITCP_protocol<Client>::Game_stone::Color::Black),
  m_name(name)
{
  m_board.fill(None);
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
  throw std::logic_error("leave game");
}

void	Game::put_stone_game(ITCP_protocol<Client> &itcp_protocol, typename ITCP_protocol<Client>::Game_stone *stone)
{
  if (m_is_start == false)
    ;
  if (stone->x >= m_size || stone->y >= m_size)
    ;
  if (m_board[stone->y * m_size + stone->x] == None)
    ;
  if (&itcp_protocol == m_black)
    {
      if (m_turn == ITCP_protocol<Client>::Game_stone::Color::White)
	;
      m_turn = ITCP_protocol<Client>::Game_stone::Color::White;
      m_board[stone->y * m_size + stone->x] = Black;
    }
  else if (&itcp_protocol == m_white)
    {
      if (m_turn == ITCP_protocol<Client>::Game_stone::Color::Black)
	;
      m_turn = ITCP_protocol<Client>::Game_stone::Color::Black;
      m_board[stone->y * m_size + stone->x] = White;
    }
  else
    throw std::logic_error("Satan is here");
  m_white->send_game_stone_put(*stone);
  m_black->send_game_stone_put(*stone);
}

void	Game::change_param_game(ITCP_protocol<Client> &itcp_protocol, typename ITCP_protocol<Client>::Game_param *param)
{
}

void	Game::list_param_game(ITCP_protocol<Client> &itcp_protocol, std::list<typename ITCP_protocol<Client>::Game_param *> *params)
{
}

void	Game::start_game(ITCP_protocol<Client> &itcp_protocol)
{
  if (m_white == nullptr || m_black == nullptr)
    ;
  else if (m_white_is_ready == false || m_black_is_ready == false)
    ;
  else
    m_is_start = true;
}

void	Game::ready_game(ITCP_protocol<Client> &itcp_protocol, bool ready)
{
  if (&itcp_protocol == m_black)
    m_black_is_ready = ready;
  else if (&itcp_protocol == m_black)
    m_white_is_ready = ready;
  else
    throw std::logic_error("Impossible has happen");
}
