#ifndef		ITCP_PROTOCOL_HPP_
# define	ITCP_PROTOCOL_HPP_

# include	<cstdint>
# include	<string>
# include	<list>
# include   <stdexcept>
# include	"ITCP_client.hpp"
# include	"TCP_packet_recv.hpp"
# include	"TCP_packet_send.hpp"

namespace iprotocol
{
    enum    Error : uint8_t
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
        All_player_are_not_ready,
        Game_stone_double_three_not_allow,
        Game_stone_case_not_empty,
        Game_stone_coordinate_not_valide,
        Game_stone_not_your_turn,
    };
    char const   *get_str_error(Error error);
    std::ostream    &operator<<(std::ostream &os, Error error);
    struct  Game
    {
        std::string *name;
    };

    struct  Message
    {
        std::string *name;
        std::string *message;
    };

    struct  Game_result
    {
		enum    Color : uint8_t
		{
			White = 0,
			Black,
		}	winner;
    };

    struct  Game_param
    {
        bool    three_and_three;
        bool    five_breakable;
        bool    ai_white;
        bool    ai_black;
    };

    struct  Game_player_param
    {
        std::string *name;
        enum    Type : uint8_t
        {
            White,
            Black,
            Spectator,
        }       type;
    };

    struct  Game_stone
    {
        uint8_t x;
        uint8_t y;
        enum    Color : uint8_t
        {
            White = 0,
            Black,
            None
        }       color;
      Game_stone(uint8_t _x, uint8_t _y, Color _color);
      Game_stone(void);
      Color operator!(void);
    };

    struct  Game_score
    {
        uint8_t white_stone_taken;
        uint8_t black_stone_taken;
    };

    template<typename T>
    class	ITCP_protocol
    {
    public:
        class	Callback
        {
        public:
            virtual ~Callback(void)
            {
            }
            virtual void    result(ITCP_protocol &itcp_protocol, Error error) = 0;
            virtual void	connect(ITCP_protocol &itcp_protocol, uint8_t version, std::string *login, std::string *password) = 0;
            virtual void	disconnect(ITCP_protocol &itcp_protocol) = 0;
            virtual void	ping(ITCP_protocol &itcp_protocol) = 0;
            virtual void	pong(ITCP_protocol &itcp_protocol) = 0;
            virtual void	game_create(ITCP_protocol &itcp_protocol, Game *game) = 0;
            virtual void    game_delete(ITCP_protocol &itcp_protocol, Game *game) = 0;
            virtual void	game_join(ITCP_protocol &itcp_protocol, Game *game) = 0;
            virtual void	game_leave(ITCP_protocol &itcp_protocol) = 0;
            virtual void    game_param(ITCP_protocol &itcp_protocol, Game_param *param) = 0;
            virtual void    game_player_param(ITCP_protocol &itcp_protocol, Game_player_param *param) = 0;
            virtual void	game_player_join(ITCP_protocol &itcp_protocol, std::string *name) = 0;
            virtual void	game_player_leave(ITCP_protocol &itcp_protocol, std::string *name) = 0;
            virtual void    game_stone_put(ITCP_protocol &itcp_protocol, Game_stone *stone) = 0;
            virtual void	game_start(ITCP_protocol &itcp_protocol) = 0;
            virtual void	game_ready(ITCP_protocol &itcp_protocol, bool ready) = 0;
            virtual void    game_score(ITCP_protocol &itcp_protocol, Game_score *game_score) = 0;
            virtual void    game_help(ITCP_protocol &itcp_protocol) = 0;
            virtual void    game_hint(ITCP_protocol &itcp_protocol, Game_stone *stone) = 0;
            virtual void    game_result(ITCP_protocol &itcp_protocol, Game_result *game_result) = 0;
            virtual void	game_message(ITCP_protocol &itcp_protocol, Message *message) = 0;
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
        virtual void	send_game_create(Game const &game) = 0;
        virtual void    send_game_delete(Game const &game) = 0;
        virtual void	send_game_join(Game const &game) = 0;
        virtual void	send_game_leave(void) = 0;
        virtual void    send_game_stone_put(Game_stone const &stone) = 0;
        virtual void    send_game_param(Game_param const &param) = 0;
        virtual void	send_game_player_param(Game_player_param const &param) = 0;
        virtual void	send_game_player_join(std::string const &name) = 0;
        virtual void	send_game_player_leave(std::string const &name) = 0;
        virtual void	send_game_start(void) = 0;
        virtual void	send_game_ready(bool ready) = 0;
        virtual void    send_game_score(Game_score const &score) = 0;
        virtual void    send_game_result(Game_result const &result) = 0;
        virtual void    send_game_help(void) = 0;
        virtual void    send_game_hint(Game_stone const &stone) = 0;
        virtual void	send_game_message(Message const &message) = 0;

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
}

#endif		/* !ITCP_PROTOCOL_HPP_ */
