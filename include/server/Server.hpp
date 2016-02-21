//
// Server.hpp for Server in /home/plasko_a/projet/gomoku/include/server
//
// Made by Antoine Plaskowski
// Login   <plasko_a@epitech.eu>
//
// Started on  Tue Jan 26 17:48:04 2016 Antoine Plaskowski
// Last update Thu Jan 28 13:04:00 2016 Antoine Plaskowski
//

#ifndef		SERVER_HPP_
# define	SERVER_HPP_

# include	<list>
# include   <string>
# include   <chrono>
# include	"ITCP_server.hpp"
# include	"ITCP_protocol.hpp"
# include	"Select.hpp"
# include	"Client.hpp"
# include   "Options.hpp"
# include	"Game.hpp"

class	Server : public iprotocol::ITCP_protocol<Client>::Callback
{
public:
    Server(Options const &options);
private:
    Server(ITCP_server *);
public:
    ~Server(void);
    void    pre_run(void);
    void	run(void);
    void	result(iprotocol::ITCP_protocol<Client> &itcp_protocol, iprotocol::Error error);
    void	connect(iprotocol::ITCP_protocol<Client> &itcp_protocol, uint8_t version, std::string *login, std::string *password);
    void	disconnect(iprotocol::ITCP_protocol<Client> &itcp_protocol);
    void	ping(iprotocol::ITCP_protocol<Client> &itcp_protocol);
    void	pong(iprotocol::ITCP_protocol<Client> &itcp_protocol);
    void	create_game(iprotocol::ITCP_protocol<Client> &itcp_protocol, iprotocol::Game *game);
    void	join_game(iprotocol::ITCP_protocol<Client> &itcp_protocol, iprotocol::Game *game);
    void	leave_game(iprotocol::ITCP_protocol<Client> &itcp_protocol);
    void	put_stone_game(iprotocol::ITCP_protocol<Client> &itcp_protocol, iprotocol::Game_stone *stone);
    void    change_param_player_game(iprotocol::ITCP_protocol<Client> &itcp_protocol, iprotocol::Game_player_param *param);
    void	change_param_game(iprotocol::ITCP_protocol<Client> &itcp_protocol, iprotocol::Game_param *param);
    void    list_param_player_game(iprotocol::ITCP_protocol<Client> &itcp_protocol, std::list<iprotocol::Game_player_param *> *params);
    void    list_param_game(iprotocol::ITCP_protocol<Client> &itcp_protocol, std::list<iprotocol::Game_param *> *params);
    void	game_created(iprotocol::ITCP_protocol<Client> &itcp_protocol, iprotocol::Game *game);
    void	game_player_joined(iprotocol::ITCP_protocol<Client> &itcp_protocol, std::string *name);
    void	game_player_left(iprotocol::ITCP_protocol<Client> &itcp_protocol, std::string *name);
    void    game_player_param_changed(iprotocol::ITCP_protocol<Client> &itcp_protocol, iprotocol::Game_player_param *param);
    void	game_param_changed(iprotocol::ITCP_protocol<Client> &itcp_protocol, iprotocol::Game_param *param);
    void	game_stone_put(iprotocol::ITCP_protocol<Client> &itcp_protocol, iprotocol::Game_stone *stone);
    void	game_deleted(iprotocol::ITCP_protocol<Client> &itcp_protocol, iprotocol::Game *game);
    void	start_game(iprotocol::ITCP_protocol<Client> &itcp_protocol);
    void	ready_game(iprotocol::ITCP_protocol<Client> &itcp_protocol, bool ready);
    void	result_game(iprotocol::ITCP_protocol<Client> &itcp_protocol, iprotocol::Game_result *game_result);
    void	message(iprotocol::ITCP_protocol<Client> &itcp_protocol, iprotocol::Message *message);
private:
    ITCP_server const   *m_itcp_server;
    ISelect	*m_iselect;
    std::chrono::seconds	m_timeout;
    std::list<Game *>	m_games;
    std::list<iprotocol::ITCP_protocol<Client> *>  m_itcp_protocols;
    std::list<iprotocol::ITCP_protocol<Client> *>  m_disconnecteds;
};

class	AServer_exception : public std::exception
{
public:
    AServer_exception(void) noexcept;
    AServer_exception(AServer_exception const &) noexcept;
    virtual ~AServer_exception(void) noexcept;
    virtual char const  *what(void) const noexcept;
    AServer_exception	&operator=(AServer_exception const &) noexcept;
};

class	Server_exception_client_transfer : public AServer_exception
{
public:
    Server_exception_client_transfer(Game *game) noexcept;
    Server_exception_client_transfer(Server_exception_client_transfer const &) noexcept;
    ~Server_exception_client_transfer(void) noexcept;
    char const  *what(void) const noexcept;
    Server_exception_client_transfer	&operator=(Server_exception_client_transfer const &) noexcept;
public:
    Game	*m_game;
};

class   Server_exception_client_disconnected : public AServer_exception
{
public:
    Server_exception_client_disconnected(void) noexcept;
    Server_exception_client_disconnected(Server_exception_client_disconnected const &) noexcept;
    ~Server_exception_client_disconnected(void) noexcept;
    char const  *what(void) const noexcept;
    Server_exception_client_disconnected	&operator=(Server_exception_client_disconnected const &) noexcept;
};

#endif		/* !SERVER_HPP_ */
