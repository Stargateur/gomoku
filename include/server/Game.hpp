//
// Game.hpp for Game in /home/plasko_a/projet/gomoku
//
// Made by Antoine Plaskowski
// Login   <antoine.plaskowski@epitech.eu>
//
// Started on  Wed Jan 27 14:45:21 2016 Antoine Plaskowski
// Last update Thu Jan 28 10:47:25 2016 Antoine Plaskowski
//

#ifndef		GAME_HPP_
# define	GAME_HPP_

# include   <map>
# include   "ISelect.hpp"
# include	"Client.hpp"
# include   "ITime.hpp"
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
    void	run(ISelect &iselect, ITime &itime);
    void    add_player(iprotocol::ITCP_protocol<Client>  *player);
private:
    void    delete_player(std::list<iprotocol::ITCP_protocol<Client> *>::iterator &it);
    void    set_name(std::string *name);
public:
    std::list<iprotocol::ITCP_protocol<Client> *> const    &get_players(void) const;
    std::string const	&get_name(void) const;
    void    send_game_created(iprotocol::ITCP_protocol<Client> &itcp_protocol) const;
    void    send_game_deleted(iprotocol::ITCP_protocol<Client> &itcp_protocol) const;
    void	create_game(iprotocol::ITCP_protocol<Client> &itcp_protocol, iprotocol::Game *game);
    void	join_game(iprotocol::ITCP_protocol<Client> &itcp_protocol, iprotocol::Game *game);
    void	leave_game(iprotocol::ITCP_protocol<Client> &itcp_protocol);
    void	put_stone_game(iprotocol::ITCP_protocol<Client> &itcp_protocol, iprotocol::Game_stone *stone);
    void    change_param_player_game(iprotocol::ITCP_protocol<Client> &itcp_protocol, iprotocol::Game_player_param *param);
    void    change_param_game(iprotocol::ITCP_protocol<Client> &itcp_protocol, iprotocol::Game_param *param);
    void	start_game(iprotocol::ITCP_protocol<Client> &itcp_protocol);
    void	ready_game(iprotocol::ITCP_protocol<Client> &itcp_protocol, bool ready);
    void    result_game(iprotocol::ITCP_protocol<Client> &itcp_protocol, iprotocol::Game_result *game_result);
private:
    bool	m_is_start;
    std::string	*m_name;
    Arbitre m_arbitre;
    Black	m_black;
    White   m_white;
    ITime   *m_timeout;
    std::list<iprotocol::Game_param *>  m_param;
    std::list<iprotocol::Game_player_param *>  m_param_player;
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
