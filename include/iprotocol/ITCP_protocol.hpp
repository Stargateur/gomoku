//
// ITCP_protocol.hpp for ITCP_protocol in /home/plasko_a/projet/cplusplus/rtype/include/iprotocol
// 
// Made by Antoine Plaskowski
// Login   <antoine.plaskowski@epitech.eu>
// 
// Started on  Sun Dec  6 03:35:29 2015 Antoine Plaskowski
// Last update Tue Jan 26 14:04:05 2016 Antoine Plaskowski
//

#ifndef		ITCP_PROTOCOL_HPP_
# define	ITCP_PROTOCOL_HPP_

# include	<cstdint>
# include	<string>
# include	<list>
# include	"ITime.hpp"
# include	"ITCP_client.hpp"
# include	"TCP_packet_recv.hpp"
# include	"TCP_packet_send.hpp"

template<typename T>
class	ITCP_protocol
{
public:
  enum	Error : uint8_t
  {
    NONE = 0,
      IGNORED,
      UNKNOW,
      WRONGLOGIN
  };
  
  struct	Game
  {
    std::string	*name;
    std::string	*owner;
  };
  
  struct	Message
  {
    std::string	*name;
    std::string	*message;
  };
  
  struct	Game_result
  {
    std::string	*name;
    std::string	*value;
  };
  
  struct	Game_param
  {
    std::string	*name;
    std::string	*value;
  };
  
  struct	Game_stone
  {
    uint8_t	x;
    uint8_t	y;
    enum : uint8_t
      {
	WHITE = 0,
	BLACK
      }		color;
  };
  
  class	Callback
  {
  public:
    virtual ~Callback(void)
    {
    }
    virtual void	result(ITCP_protocol &itcp_protocol, Error error) = 0;
    virtual void	connect(ITCP_protocol &itcp_protocol, std::string *login, std::string *password) = 0;
    virtual void	disconnect(ITCP_protocol &itcp_protocol) = 0;
    virtual void	ping(ITCP_protocol &itcp_protocol) = 0;
    virtual void	pong(ITCP_protocol &itcp_protocol) = 0;
    virtual void	create_game(ITCP_protocol &itcp_protocol, Game *game) = 0;
    virtual void	join_game(ITCP_protocol &itcp_protocol, Game *game) = 0;
    virtual void	leave_game(ITCP_protocol &itcp_protocol) = 0;
    virtual void	put_stone_game(ITCP_protocol &itcp_protocol, Game_stone *stone) = 0;
    virtual void	change_param_game(ITCP_protocol &itcp_protocol, Game_param *param) = 0;
    virtual void	list_param_game(ITCP_protocol &itcp_protocol, std::iterator<std::input_iterator_tag, Game_param *> const &begin, std::iterator<std::input_iterator_tag, Game_param *> const &end) = 0;
    virtual void	game_created(ITCP_protocol &itcp_protocol, Game *game) = 0;
    virtual void	game_player_joined(ITCP_protocol &itcp_protocol, std::string *name) = 0;
    virtual void	game_player_left(ITCP_protocol &itcp_protocol, std::string *name) = 0;
    virtual void	game_param_changed(ITCP_protocol &itcp_protocol, Game_param *param) = 0;
    virtual void	game_stone_put(ITCP_protocol &itcp_protocol, Game_stone *stone) = 0;
    virtual void	game_deleted(ITCP_protocol &itcp_protocol, Game *game) = 0;
    virtual void	start_game(ITCP_protocol &itcp_protocol) = 0;
    virtual void	ready_game(ITCP_protocol &itcp_protocol, bool ready) = 0;
    virtual void	result_game(ITCP_protocol &itcp_protocol, Game_result *game_result) = 0;
    virtual void	message(ITCP_protocol &itcp_protocol, Message *message) = 0;
  };
public:
  virtual ~ITCP_protocol(void)
  {
  }
  virtual void	set_callback(Callback *callback) = 0;
  virtual void	set_data(T *data) = 0;
  virtual T	*get_data(void) = 0;
  virtual T const	*get_data(void) const = 0;
  virtual bool	want_send(void) const = 0;
  virtual bool	want_recv(void) const = 0;
  virtual void	send(ITCP_client const &socket) = 0;
  virtual void	recv(ITCP_client const &socket) = 0;
  virtual void	send_result(Error error) = 0;
  virtual void	send_connect(std::string const &login, std::string const &password) = 0;
  virtual void	send_disconnect(void) = 0;
  virtual void	send_ping(void) = 0;
  virtual void	send_pong(void) = 0;
  virtual void	send_create_game(Game const &game) = 0;
  virtual void	send_join_game(Game const &game) = 0;
  virtual void	send_leave_game(void) = 0;
  virtual void	send_put_stone_game(Game_stone const &stone) = 0;
  virtual void	send_change_param_game(Game_param const &param) = 0;
  virtual void	send_list_param_game(std::iterator<std::input_iterator_tag, Game_param *> const &begin, std::iterator<std::input_iterator_tag, Game_param *> const &end) = 0;
  virtual void	send_game_created(Game const &game) = 0;
  virtual void	send_game_player_joined(std::string const &name) = 0;
  virtual void	send_game_player_left(std::string const &name) = 0;
  virtual void	send_game_param_changed(Game_param const &param) = 0;
  virtual void	send_game_stone_put(Game_stone const &stone) = 0;
  virtual void	send_game_deleted(Game const &game) = 0;
  virtual void	send_start_game(void) = 0;
  virtual void	send_ready_game(bool ready) = 0;
  virtual void	send_result_game(Game_result const &result) = 0;
  virtual void	send_message(Message const &message) = 0;
};

#endif		/* !ITCP_PROTOCOL_HPP_ */
