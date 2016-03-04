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
    Server(std::string const &options);
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
    void	game_create(iprotocol::ITCP_protocol<Client> &itcp_protocol, iprotocol::Game *game);
    void    game_delete(iprotocol::ITCP_protocol<Client> &itcp_protocol, iprotocol::Game *game);
    void	game_join(iprotocol::ITCP_protocol<Client> &itcp_protocol, iprotocol::Game *game);
    void	game_leave(iprotocol::ITCP_protocol<Client> &itcp_protocol);
    void    game_stone_put(iprotocol::ITCP_protocol<Client> &itcp_protocol, iprotocol::Game_stone *stone);
    void    game_player_param(iprotocol::ITCP_protocol<Client> &itcp_protocol, iprotocol::Game_player_param *param);
    void	game_param(iprotocol::ITCP_protocol<Client> &itcp_protocol, iprotocol::Game_param *param);
    void	game_player_join(iprotocol::ITCP_protocol<Client> &itcp_protocol, std::string *name);
    void	game_player_leave(iprotocol::ITCP_protocol<Client> &itcp_protocol, std::string *name);
    void	game_start(iprotocol::ITCP_protocol<Client> &itcp_protocol);
    void	game_ready(iprotocol::ITCP_protocol<Client> &itcp_protocol, bool ready);
    void    game_score(iprotocol::ITCP_protocol<Client> &itcp_protocol, iprotocol::Game_score *game_score);
    void    game_help(iprotocol::ITCP_protocol<Client> &itcp_protocol);
    void    game_hint(iprotocol::ITCP_protocol<Client> &itcp_protocol, iprotocol::Game_stone *stone);
    void    game_result(iprotocol::ITCP_protocol<Client> &itcp_protocol, iprotocol::Game_result *game_result);
    void	game_message(iprotocol::ITCP_protocol<Client> &itcp_protocol, iprotocol::Message *message);
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
