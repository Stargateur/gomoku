//
// Client.hpp for Client in /home/plasko_a/projet/gomoku/include
// 
// Made by Antoine Plaskowski
// Login   <antoine.plaskowski@epitech.eu>
// 
// Started on  Wed Jan 27 11:00:32 2016 Antoine Plaskowski
// Last update Wed Jan 27 11:18:31 2016 Antoine Plaskowski
//

#ifndef		CLIENT_HPP_
# define	CLIENT_HPP_

# include	"ITCP_protocol.hpp"
# include	"ITCP_client.hpp"
# include	"ISelect.hpp"

class Client : public ITCP_protocol<ITCP_client>::Callback
{
public:
  Client(void);
  ~Client(void);
  void	run(void);
  void	result(ITCP_protocol<ITCP_client> &itcp_protocol, typename ITCP_protocol<ITCP_client>::Error error);
  void	connect(ITCP_protocol<ITCP_client> &itcp_protocol, uint8_t version, std::string *login, std::string *password);
  void	disconnect(ITCP_protocol<ITCP_client> &itcp_protocol);
  void	ping(ITCP_protocol<ITCP_client> &itcp_protocol);
  void	pong(ITCP_protocol<ITCP_client> &itcp_protocol);
  void	create_game(ITCP_protocol<ITCP_client> &itcp_protocol, typename ITCP_protocol<ITCP_client>::Game *game);
  void	join_game(ITCP_protocol<ITCP_client> &itcp_protocol, typename ITCP_protocol<ITCP_client>::Game *game);
  void	leave_game(ITCP_protocol<ITCP_client> &itcp_protocol);
  void	put_stone_game(ITCP_protocol<ITCP_client> &itcp_protocol, typename ITCP_protocol<ITCP_client>::Game_stone *stone);
  void	change_param_game(ITCP_protocol<ITCP_client> &itcp_protocol, typename ITCP_protocol<ITCP_client>::Game_param *param);
  void	list_param_game(ITCP_protocol<ITCP_client> &itcp_protocol, std::list<typename ITCP_protocol<ITCP_client>::Game_param *> *params);
  void	game_created(ITCP_protocol<ITCP_client> &itcp_protocol, typename ITCP_protocol<ITCP_client>::Game *game);
  void	game_player_joined(ITCP_protocol<ITCP_client> &itcp_protocol, std::string *name);
  void	game_player_left(ITCP_protocol<ITCP_client> &itcp_protocol, std::string *name);
  void	game_param_changed(ITCP_protocol<ITCP_client> &itcp_protocol, typename ITCP_protocol<ITCP_client>::Game_param *param);
  void	game_stone_put(ITCP_protocol<ITCP_client> &itcp_protocol, typename ITCP_protocol<ITCP_client>::Game_stone *stone);
  void	game_deleted(ITCP_protocol<ITCP_client> &itcp_protocol, typename ITCP_protocol<ITCP_client>::Game *game);
  void	start_game(ITCP_protocol<ITCP_client> &itcp_protocol);
  void	ready_game(ITCP_protocol<ITCP_client> &itcp_protocol, bool ready);
  void	result_game(ITCP_protocol<ITCP_client> &itcp_protocol, typename ITCP_protocol<ITCP_client>::Game_result *game_result);
  void	message(ITCP_protocol<ITCP_client> &itcp_protocol, typename ITCP_protocol<ITCP_client>::Message *message);
private:
  ITCP_protocol<ITCP_client>	*m_itcp_protocol;
  ISelect	*m_iselect;
};

#endif		/* !CLIENT_HPP_ */
