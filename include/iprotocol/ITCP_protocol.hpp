//
// ITCP_protocol.hpp for ITCP_protocol in /home/plasko_a/projet/cplusplus/rtype/include/iprotocol
//
// Made by Antoine Plaskowski
// Login   <antoine.plaskowski@epitech.eu>
//
// Started on  Sun Dec  6 03:35:29 2015 Antoine Plaskowski
// Last update Wed Feb 17 14:36:04 2016 Antoine Plaskowski
//

#ifndef		ITCP_PROTOCOL_HPP_
# define	ITCP_PROTOCOL_HPP_

# include	<cstdint>
# include	<string>
# include	<list>
# include   <stdexcept>
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
        None = 0,
        Ignore,
        Unknow,
        Disconnected,
        Not_connected,
        Timeout,
        Wrong_login,
        Wrong_password,
        Wrong_version,
        Login_already_use,
        Game_already_exist,
        Game_not_exist,
        Already_in_game,
        Not_in_game,
        Packet_not_allowed,
        Game_param_not_exist,
        Game_player_param_not_exist,
        All_player_are_not_ready,
        Game_stone_double_three_not_allow,
        Game_stone_case_not_empty,
        Game_stone_coordinate_not_valide,
        Game_stone_not_your_turn,
    };

    struct	Game
    {
        std::string	*name;
    };

    struct	Message
    {
        std::string	*name;
        std::string	*message;
    };

    struct	Game_result
    {
        std::string *winner;
    };

    struct	Game_param
    {
        std::string	*name;
        std::string	*value;
    };

    struct  Game_player_param
    {
        std::string *name;
        std::string *value;
    };

    struct	Game_stone
    {
        uint8_t	x;
        uint8_t	y;
        enum	Color : uint8_t
        {
            White = 0,
            Black,
            None
        }		color;
      Game_stone(uint8_t _x, uint8_t _y, Color _color) :
	x(_x),
	y(_y),
	color(_color)
      {
      }
      Game_stone(void) :
	Game_stone(0, 0, None)
      {
      }
      Color	operator!(void)
      {
	if (color == Black)
	  return White;
	else if (color == White)
	  return Black;
	else
	  return None;
      }
    };

    class	Callback
    {
    public:
        virtual ~Callback(void)
        {
        }
        virtual void	result(ITCP_protocol &itcp_protocol, Error error) = 0;
        virtual void	connect(ITCP_protocol &itcp_protocol, uint8_t version, std::string *login, std::string *password) = 0;
        virtual void	disconnect(ITCP_protocol &itcp_protocol) = 0;
        virtual void	ping(ITCP_protocol &itcp_protocol) = 0;
        virtual void	pong(ITCP_protocol &itcp_protocol) = 0;
        virtual void	create_game(ITCP_protocol &itcp_protocol, Game *game) = 0;
        virtual void	join_game(ITCP_protocol &itcp_protocol, Game *game) = 0;
        virtual void	leave_game(ITCP_protocol &itcp_protocol) = 0;
        virtual void	put_stone_game(ITCP_protocol &itcp_protocol, Game_stone *stone) = 0;
        virtual void    change_param_player_game(ITCP_protocol &itcp_protocol, Game_player_param *param) = 0;
        virtual void    change_param_game(ITCP_protocol &itcp_protocol, Game_param *param) = 0;
        virtual void    list_param_game(ITCP_protocol &itcp_protocol, std::list<Game_param *> *params) = 0;
        virtual void    list_param_player_game(ITCP_protocol &itcp_protocol, std::list<Game_player_param *> *params) = 0;
        virtual void	game_created(ITCP_protocol &itcp_protocol, Game *game) = 0;
        virtual void	game_player_joined(ITCP_protocol &itcp_protocol, std::string *name) = 0;
        virtual void	game_player_left(ITCP_protocol &itcp_protocol, std::string *name) = 0;
        virtual void    game_player_param_changed(ITCP_protocol &itcp_protocol, Game_player_param *param) = 0;
        virtual void	game_param_changed(ITCP_protocol &itcp_protocol, Game_param *param) = 0;
        virtual void	game_stone_put(ITCP_protocol &itcp_protocol, Game_stone *stone) = 0;
        virtual void	game_deleted(ITCP_protocol &itcp_protocol, Game *game) = 0;
        virtual void	start_game(ITCP_protocol &itcp_protocol) = 0;
        virtual void	ready_game(ITCP_protocol &itcp_protocol, bool ready) = 0;
        virtual void    result_game(ITCP_protocol &itcp_protocol, Game_result *game_result) = 0;
        virtual void	message(ITCP_protocol &itcp_protocol, Message *message) = 0;
    };
public:
    virtual ~ITCP_protocol(void)
    {
    }
    virtual uint8_t	get_version(void) const = 0;
    virtual void	set_callback(Callback *callback) = 0;
    virtual Callback	*get_callback(void) const = 0;
    virtual void    set_data(T *data) = 0;
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
    virtual void    send_change_param_game(Game_param const &param) = 0;
    virtual void	send_change_param_player_game(Game_player_param const &param) = 0;
    virtual void    send_list_param_game(std::list<Game_param *> const &params) = 0;
    virtual void    send_list_param_player_game(std::list<Game_player_param *> const &params) = 0;
    virtual void	send_game_created(Game const &game) = 0;
    virtual void	send_game_player_joined(std::string const &name) = 0;
    virtual void	send_game_player_left(std::string const &name) = 0;
    virtual void    send_game_player_param_changed(Game_player_param const &param) = 0;
    virtual void	send_game_param_changed(Game_param const &param) = 0;
    virtual void	send_game_stone_put(Game_stone const &stone) = 0;
    virtual void	send_game_deleted(Game const &game) = 0;
    virtual void	send_start_game(void) = 0;
    virtual void	send_ready_game(bool ready) = 0;
    virtual void	send_result_game(Game_result const &result) = 0;
    virtual void	send_message(Message const &message) = 0;
    static char const	*get_str_error(Error error)
    {
        switch (error)
        {
        case None:
            return ("None");
        case Ignore:
            return ("Ignore");
        case Unknow:
            return ("Unknow");
        case Disconnected:
            return ("Disconnected");
        case Not_connected:
            return ("Not_connected");
        case Timeout:
            return ("Timeout");
        case Wrong_login:
            return ("Wrong_login");
        case Wrong_password:
            return ("Wrong password");
        case Wrong_version:
            return ("Wrong_version");
        case Login_already_use:
            return ("Login_already_use");
        case Game_already_exist:
            return ("Game_already_exist");
        case Game_not_exist:
            return ("Game_not_exist");
        case Already_in_game:
            return ("Already_in_game");
        case Not_in_game:
            return ("Not_in_game");
        case Packet_not_allowed:
            return ("Packet_not_allowed");
        case Game_param_not_exist:
            return ("Game_param_not_exist");
        case Game_player_param_not_exist:
            return ("Game_player_param_not_exist");
        case All_player_are_not_ready:
            return ("All_player_are_not_ready");
        case Game_stone_double_three_not_allow:
            return ("Game_stone_double_three_not_allow");
        case Game_stone_case_not_empty:
            return ("Game_stone_case_not_empty");
        case Game_stone_coordinate_not_valide:
            return ("Game_stone_coordinate_not_valide");
        case Game_stone_not_your_turn:
            return ("Game_stone_not_your_turn");
        };
        throw std::logic_error("Unknown error code");
    }
};

class ITCP_protocol_exception : public std::exception
{
public:
    ITCP_protocol_exception(void) noexcept;
    ITCP_protocol_exception(ITCP_protocol_exception const &) noexcept; 
    ~ITCP_protocol_exception(void) noexcept;
    ITCP_protocol_exception   &operator=(ITCP_protocol_exception const &) noexcept;
    char const  *what(void) const noexcept;
};

template<typename T>
std::ostream    &operator<<(std::ostream &os, typename ITCP_protocol<T>::Error error)
{
    return (os << ITCP_protocol<T>::get_str_error(error));
}

#endif		/* !ITCP_PROTOCOL_HPP_ */
