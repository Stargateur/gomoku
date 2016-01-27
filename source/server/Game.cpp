//
// Game.cpp for Game in /home/plasko_a/projet/gomoku
// 
// Made by Antoine Plaskowski
// Login   <antoine.plaskowski@epitech.eu>
// 
// Started on  Wed Jan 27 15:21:28 2016 Antoine Plaskowski
// Last update Wed Jan 27 18:09:52 2016 Antoine Plaskowski
//

#include	"Game.hpp"

Game::Game(typename ITCP_protocol<Client>::Callback &callback) :
  m_callback(callback),
  m_is_start(false),
  m_white_is_ready(false),
  m_black_is_ready(false),
  m_turn(ITCP_protocol<Client>::Game_stone::Color::Black)
{
  m_board.fill(None);
}

Game::~Game(void)
{
}

void	Game::result(ITCP_protocol<Client> &itcp_protocol, typename ITCP_protocol<Client>::Error error)
{
  m_callback.result(itcp_protocol, error);
}

void	Game::connect(ITCP_protocol<Client> &itcp_protocol, uint8_t version, std::string *login, std::string *password)
{
  throw std::logic_error("Already connected");
}

void	Game::disconnect(ITCP_protocol<Client> &itcp_protocol)
{
  m_callback.disconnect(itcp_protocol);
}

void	Game::ping(ITCP_protocol<Client> &itcp_protocol)
{
  m_callback.ping(itcp_protocol);
}

void	Game::pong(ITCP_protocol<Client> &itcp_protocol)
{
  m_callback.pong(itcp_protocol);
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

void	Game::game_created(ITCP_protocol<Client> &itcp_protocol, typename ITCP_protocol<Client>::Game *game)
{
  m_callback.game_created(itcp_protocol, game);
}

void	Game::game_player_joined(ITCP_protocol<Client> &itcp_protocol, std::string *name)
{
  m_callback.game_player_joined(itcp_protocol, name);
}

void	Game::game_player_left(ITCP_protocol<Client> &itcp_protocol, std::string *name)
{
  m_callback.game_player_left(itcp_protocol, name);
}

void	Game::game_param_changed(ITCP_protocol<Client> &itcp_protocol, typename ITCP_protocol<Client>::Game_param *param)
{
  m_callback.game_param_changed(itcp_protocol, param);
}

void	Game::game_stone_put(ITCP_protocol<Client> &itcp_protocol, typename ITCP_protocol<Client>::Game_stone *stone)
{
  m_callback.game_stone_put(itcp_protocol, stone);
}

void	Game::game_deleted(ITCP_protocol<Client> &itcp_protocol, typename ITCP_protocol<Client>::Game *game)
{
  m_callback.game_deleted(itcp_protocol, game);
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

void	Game::result_game(ITCP_protocol<Client> &itcp_protocol, typename ITCP_protocol<Client>::Game_result *game_result)
{
  m_callback.result_game(itcp_protocol, game_result);
}

void	Game::message(ITCP_protocol<Client> &itcp_protocol, typename ITCP_protocol<Client>::Message *message)
{
  m_callback.message(itcp_protocol, message);
}
