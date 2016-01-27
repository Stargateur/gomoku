//
// Game.hpp for Game in /home/plasko_a/projet/gomoku
// 
// Made by Antoine Plaskowski
// Login   <antoine.plaskowski@epitech.eu>
// 
// Started on  Wed Jan 27 14:45:21 2016 Antoine Plaskowski
// Last update Wed Jan 27 17:43:09 2016 Antoine Plaskowski
//

#ifndef		GAME_HPP_
# define	GAME_HPP_

# include	<array>
# include	"Client.hpp"
# include	"ITCP_protocol.hpp"

class	Game : public ITCP_protocol<Client>::Callback
{
public:
  Game(typename ITCP_protocol<Client>::Callback &callback);
  ~Game(void);
  void	run(void);
  void	result(ITCP_protocol<Client> &itcp_protocol, typename ITCP_protocol<Client>::Error error);
  void	connect(ITCP_protocol<Client> &itcp_protocol, uint8_t version, std::string *login, std::string *password);
  void	disconnect(ITCP_protocol<Client> &itcp_protocol);
  void	ping(ITCP_protocol<Client> &itcp_protocol);
  void	pong(ITCP_protocol<Client> &itcp_protocol);
  void	create_game(ITCP_protocol<Client> &itcp_protocol, typename ITCP_protocol<Client>::Game *game);
  void	join_game(ITCP_protocol<Client> &itcp_protocol, typename ITCP_protocol<Client>::Game *game);
  void	leave_game(ITCP_protocol<Client> &itcp_protocol);
  void	put_stone_game(ITCP_protocol<Client> &itcp_protocol, typename ITCP_protocol<Client>::Game_stone *stone);
  void	change_param_game(ITCP_protocol<Client> &itcp_protocol, typename ITCP_protocol<Client>::Game_param *param);
  void	list_param_game(ITCP_protocol<Client> &itcp_protocol, std::list<typename ITCP_protocol<Client>::Game_param *> *params);
  void	game_created(ITCP_protocol<Client> &itcp_protocol, typename ITCP_protocol<Client>::Game *game);
  void	game_player_joined(ITCP_protocol<Client> &itcp_protocol, std::string *name);
  void	game_player_left(ITCP_protocol<Client> &itcp_protocol, std::string *name);
  void	game_param_changed(ITCP_protocol<Client> &itcp_protocol, typename ITCP_protocol<Client>::Game_param *param);
  void	game_stone_put(ITCP_protocol<Client> &itcp_protocol, typename ITCP_protocol<Client>::Game_stone *stone);
  void	game_deleted(ITCP_protocol<Client> &itcp_protocol, typename ITCP_protocol<Client>::Game *game);
  void	start_game(ITCP_protocol<Client> &itcp_protocol);
  void	ready_game(ITCP_protocol<Client> &itcp_protocol, bool ready);
  void	result_game(ITCP_protocol<Client> &itcp_protocol, typename ITCP_protocol<Client>::Game_result *game_result);
  void	message(ITCP_protocol<Client> &itcp_protocol, typename ITCP_protocol<Client>::Message *message);
private:
  ITCP_protocol<Client>::Callback	&m_callback;
  bool	m_is_start;
  bool	m_white_is_ready;
  bool	m_black_is_ready;
  ITCP_protocol<Client>::Game_stone::Color	m_turn;
  static uintmax_t const	m_size = 19;
  enum	Color
    {
      White,
      Black,
      None
    };
  std::array<Color, m_size * m_size>	m_board;
public:
  ITCP_protocol<Client> *m_white;
  ITCP_protocol<Client> *m_black;
};

#endif		/* !GAME_HPP_ */
