#ifndef		GAME_HPP_
# define	GAME_HPP_

# include   <map>
# include   <chrono>
# include   "ISelect.hpp"
# include	"Client.hpp"
# include	"White.hpp"
# include   "Black.hpp"
# include   "Arbitre.hpp"
# include	"ACallback.hpp"

class	Game : public iprotocol::ACallback<Client>
{
public:
    Game(typename iprotocol::ITCP_protocol<Client>::Callback &callback, std::string *name);
    ~Game(void);
    void    pre_run(ISelect &iselect);
    void	run(ISelect &iselect);
    void    add_player(iprotocol::ITCP_protocol<Client>  *player);
private:
    void    delete_player(std::list<iprotocol::ITCP_protocol<Client> *>::iterator &it);
public:
    std::list<iprotocol::ITCP_protocol<Client> *> const    &get_players(void) const;
    std::list<iprotocol::ITCP_protocol<Client> *>   &get_players(void);
    std::string const	&get_name(void) const;
    void    send_game_create(iprotocol::ITCP_protocol<Client> &itcp_protocol) const;
    void    send_game_delete(iprotocol::ITCP_protocol<Client> &itcp_protocol) const;
    void	game_create(iprotocol::ITCP_protocol<Client> &itcp_protocol, iprotocol::Game *game);
    void	game_join(iprotocol::ITCP_protocol<Client> &itcp_protocol, iprotocol::Game *game);
    void	game_leave(iprotocol::ITCP_protocol<Client> &itcp_protocol);
    void	game_stone_put(iprotocol::ITCP_protocol<Client> &itcp_protocol, iprotocol::Game_stone *stone);
    void    game_player_param(iprotocol::ITCP_protocol<Client> &itcp_protocol, iprotocol::Game_player_param *param);
    void    game_param(iprotocol::ITCP_protocol<Client> &itcp_protocol, iprotocol::Game_param *param);
    void	game_start(iprotocol::ITCP_protocol<Client> &itcp_protocol);
    void	game_ready(iprotocol::ITCP_protocol<Client> &itcp_protocol, bool ready);
    void    game_result(iprotocol::ITCP_protocol<Client> &itcp_protocol, iprotocol::Game_result *game_result);
private:
    bool	m_is_start;
    std::string	*m_name;
    Arbitre m_arbitre;
    Black	m_black;
    White   m_white;
    std::chrono::seconds   m_timeout;
    iprotocol::Game_param  m_params;
private:
    std::list<iprotocol::ITCP_protocol<Client> *>  m_itcp_protocols;
    std::list<iprotocol::ITCP_protocol<Client> *>  m_disconnecteds;
};

class   AGame_exception : public std::exception
{
public:
    AGame_exception(void) noexcept;
    AGame_exception(AGame_exception const &) noexcept;
    virtual ~AGame_exception(void) noexcept;
    virtual char const  *what(void) const noexcept;
    AGame_exception   &operator=(AGame_exception const &) noexcept;
};

class   Game_exception_client_transfer : public AGame_exception
{
public:
    Game_exception_client_transfer(iprotocol::ITCP_protocol<Client> *client) noexcept;
    Game_exception_client_transfer(Game_exception_client_transfer const &) noexcept;
    ~Game_exception_client_transfer(void) noexcept;
    char const  *what(void) const noexcept;
    Game_exception_client_transfer    &operator=(Game_exception_client_transfer const &) noexcept;
public:
    iprotocol::ITCP_protocol<Client>    *m_client;
};

#endif		/* !GAME_HPP_ */
