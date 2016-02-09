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
# include	<string>
# include	"ITCP_server.hpp"
# include	"ITCP_protocol.hpp"
# include	"Select.hpp"
# include	"Client.hpp"
# include	"Game.hpp"

class	Server : public ITCP_protocol<Client>::Callback
{

public:
    Server(void);
private:
    Server(ITCP_server *);
    Server(ITCP_server *, ISelect *);
public:
    ~Server(void);
    void    pre_run(void) const;
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
    void    change_param_player_game(ITCP_protocol<Client> &itcp_protocol, typename ITCP_protocol<Client>::Game_player_param *param);
    void	change_param_game(ITCP_protocol<Client> &itcp_protocol, typename ITCP_protocol<Client>::Game_param *param);
    void    list_param_player_game(ITCP_protocol<Client> &itcp_protocol, std::list<typename ITCP_protocol<Client>::Game_player_param *> *params);
    void    list_param_game(ITCP_protocol<Client> &itcp_protocol, std::list<typename ITCP_protocol<Client>::Game_param *> *params);
    void	game_created(ITCP_protocol<Client> &itcp_protocol, typename ITCP_protocol<Client>::Game *game);
    void	game_player_joined(ITCP_protocol<Client> &itcp_protocol, std::string *name);
    void	game_player_left(ITCP_protocol<Client> &itcp_protocol, std::string *name);
    void    game_player_param_changed(ITCP_protocol<Client> &itcp_protocol, typename ITCP_protocol<Client>::Game_player_param *param);
    void	game_param_changed(ITCP_protocol<Client> &itcp_protocol, typename ITCP_protocol<Client>::Game_param *param);
    void	game_stone_put(ITCP_protocol<Client> &itcp_protocol, typename ITCP_protocol<Client>::Game_stone *stone);
    void	game_deleted(ITCP_protocol<Client> &itcp_protocol, typename ITCP_protocol<Client>::Game *game);
    void	start_game(ITCP_protocol<Client> &itcp_protocol);
    void	ready_game(ITCP_protocol<Client> &itcp_protocol, bool ready);
    void	result_game(ITCP_protocol<Client> &itcp_protocol, typename ITCP_protocol<Client>::Game_result *game_result);
    void	message(ITCP_protocol<Client> &itcp_protocol, typename ITCP_protocol<Client>::Message *message);
private:
    ITCP_server const   *m_itcp_server;
    ISelect	*m_iselect;
    ITime	*m_timeout;
    std::list<Game *>	m_games;
    std::list<ITCP_protocol<Client> *>  m_itcp_protocols;
    std::list<ITCP_protocol<Client> *>  m_disconnecteds;
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
