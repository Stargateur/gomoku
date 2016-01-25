//
// ITCP_protocol.hpp for ITCP_protocol in /home/plasko_a/projet/cplusplus/rtype/include/iprotocol
// 
// Made by Antoine Plaskowski
// Login   <antoine.plaskowski@epitech.eu>
// 
// Started on  Sun Dec  6 03:35:29 2015 Antoine Plaskowski
// Last update Sun Dec 27 17:32:10 2015 Antoine Plaskowski
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

class	ITCP_protocol
{
public:
  enum  Error : uint8_t
  {
    NONE = 0,
      IGNORED,
      UNKNOW,
      WRONGLOGIN
  };
  struct	Game
  {
    std::string	name;
    std::string	owner;
    uint8_t	number_player;
    uint8_t	number_player_max;
  };
  struct	Param
  {
    std::string	name;
    std::string	value;
  };
  struct	Sprite
  {
    std::string name;
    std::string checksome;
    uint64_t	id;
    uint8_t const	*data;
    uint64_t	size;
  };
  struct	Sound
  {
    std::string	name;
    std::string	checksome;
    uint64_t	id;
    uint8_t const	*data;
    uint64_t	size;
  };
  class	Callback
  {
  public:
    virtual ~Callback(void);
    virtual void	result(ITCP_protocol &itcp_protocol, Error error) = 0;
    virtual void	connect(ITCP_protocol &itcp_protocol, std::string const &login, std::string const &password) = 0;
    virtual void	disconnect(ITCP_protocol &itcp_protocol) = 0;
    virtual void	ping(ITCP_protocol &itcp_protocol) = 0;
    virtual void	pong(ITCP_protocol &itcp_protocol) = 0;
    virtual void	list_meta_games(ITCP_protocol &itcp_protocol) = 0;
    virtual void	meta_games(ITCP_protocol &itcp_protocol, std::list<Game *> const &games) = 0;
    virtual void	create_game(ITCP_protocol &itcp_protocol, Game const &game) = 0;
    virtual void	join_game(ITCP_protocol &itcp_protocol, Game const &game) = 0;
    virtual void	message(ITCP_protocol &itcp_protocol, std::string const &login, std::string const &message) = 0;
    virtual void	list_meta_params(ITCP_protocol &itcp_protocol) = 0;
    virtual void	meta_params(ITCP_protocol &itcp_protocol, std::list<Param *> const &params) = 0;
    virtual void	change_param(ITCP_protocol &itcp_protocol, Param const &param) = 0;
    virtual void	list_meta_sprites(ITCP_protocol &itcp_protocol) = 0;
    virtual void	meta_sprites(ITCP_protocol &itcp_protocol, std::list<Sprite *> const &sprites) = 0;
    virtual void	take_sprite(ITCP_protocol &itcp_protocol, Sprite const &sprite) = 0;
    virtual void	give_sprite(ITCP_protocol &itcp_protocol, Sprite const &sprite) = 0;
    virtual void	list_meta_sounds(ITCP_protocol &itcp_protocol) = 0;
    virtual void	meta_sounds(ITCP_protocol &itcp_protocol, std::list<Sound *> const &sounds) = 0;
    virtual void	take_sound(ITCP_protocol &itcp_protocol, Sound const &sound) = 0;
    virtual void	give_sound(ITCP_protocol &itcp_protocol, Sound const &sound) = 0;
    virtual void	ready(ITCP_protocol &itcp_protocol, bool ready) = 0;
    virtual void	start(ITCP_protocol &itcp_protocol, uint8_t second, uint16_t port) = 0;
    virtual void	end(ITCP_protocol &itcp_protocol, uint64_t score, bool winner) = 0;
    virtual void	leave(ITCP_protocol &itcp_protocol) = 0;  
  };
public:
  virtual ~ITCP_protocol(void);
  virtual bool	want_send(void) const = 0;
  virtual bool	want_recv(void) const = 0;
  virtual void	send(ITCP_client const &socket) = 0;
  virtual void	recv(ITCP_client const &socket) = 0;
  virtual void	send_result(Error error) = 0;
  virtual void	send_connect(std::string const &login, std::string const &password) = 0;
  virtual void	send_disconnect(void) = 0;
  virtual void	send_ping(void) = 0;
  virtual void	send_pong(void) = 0;
  virtual void	send_list_meta_games(void) = 0;
  virtual void	send_meta_games(std::list<Game *> const &games) = 0;
  virtual void	send_create_game(Game const &game) = 0;
  virtual void	send_join_game(Game const &game) = 0;
  virtual void	send_message(std::string const &login, std::string const &message) = 0;
  // virtual void	send_list_modes(void) = 0;
  // virtual void	send_meta_modes(std::list<Mode *> const &modes) = 0;
  // virtual void	send_change_mode(std::string const &mode) = 0;
  virtual void	send_list_meta_params(void) = 0;
  virtual void	send_meta_params(std::list<Param *> const &params) = 0;
  virtual void	send_change_param(Param const &param) = 0;
  virtual void	send_list_meta_sprites(void) = 0;
  virtual void	send_meta_sprites(std::list<Sprite *> const &sprites) = 0;
  virtual void	send_take_sprite(Sprite const &sprite) = 0;
  virtual void	send_give_sprite(Sprite const &sprite) = 0;
  virtual void	send_list_meta_sounds(void) = 0;
  virtual void	send_meta_sounds(std::list<Sound *> const &sounds) = 0;
  virtual void	send_take_sound(Sound const &sound) = 0;
  virtual void	send_give_sound(Sound const &sound) = 0;
  virtual void	send_ready(bool ready) = 0;
  virtual void	send_start(uint8_t second, uint16_t port) = 0;
  virtual void	send_end(uint64_t score, bool winner) = 0;
  virtual void	send_leave(void) = 0;
};

#endif		/* !ITCP_PROTOCOL_HPP_ */
