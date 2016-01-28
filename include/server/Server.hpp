//
// Server.hpp for Server in /home/plasko_a/projet/gomoku/include/server
// 
// Made by Antoine Plaskowski
// Login   <plasko_a@epitech.eu>
// 
// Started on  Tue Jan 26 17:48:04 2016 Antoine Plaskowski
// Last update Thu Jan 28 09:22:14 2016 Antoine Plaskowski
//

#ifndef		SERVER_HPP_
# define	SERVER_HPP_

# include	<list>
# include	<string>
# include	"ITCP_server.hpp"
# include	"ITCP_protocol.hpp"
# include	"IStandard.hpp"
# include	"Select.hpp"
# include	"Client.hpp"
# include	"Game.hpp"

class	Server : public ITCP_protocol<Client>::Callback
{
public:
  Server(void);
  ~Server(void);
  void	run(void);
  void	timeout(ITCP_protocol<Client> &itcp_protocol) const;
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
  ITCP_server const	*m_itcp_server;
  IStandard	*m_istandard;
  std::list<ITCP_protocol<Client> *>	m_itcp_protocols;
  ISelect	*m_iselect;
  ITime	*m_timeout;
  std::list<Game *>	m_games;
};

#endif		/* !SERVER_HPP_ */
