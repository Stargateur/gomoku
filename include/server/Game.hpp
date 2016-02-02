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

# include	<array>
# include   "ISelect.hpp"
# include	"Client.hpp"
# include   "ITime.hpp"
# include	"White.hpp"
# include	"Black.hpp"
# include	"ACallback.hpp"

class	Game : public ACallback<Client>
{
public:
    Game(typename ITCP_protocol<Client>::Callback &callback, std::string *name);
    ~Game(void);
    void    pre_run(ISelect &iselect);
    void	run(ISelect &iselect, ITime &itime);
    void    add_player(ITCP_protocol<Client>  *player);
    std::list<ITCP_protocol<Client> *> const    &get_players(void) const;
    std::string const	&get_name(void) const;
    void    timeout(ITCP_protocol<Client> &itcp_protocol) const;
    void	create_game(ITCP_protocol<Client> &itcp_protocol, typename ITCP_protocol<Client>::Game *game);
    void	join_game(ITCP_protocol<Client> &itcp_protocol, typename ITCP_protocol<Client>::Game *game);
    void	leave_game(ITCP_protocol<Client> &itcp_protocol);
    void	put_stone_game(ITCP_protocol<Client> &itcp_protocol, typename ITCP_protocol<Client>::Game_stone *stone);
    void	change_param_game(ITCP_protocol<Client> &itcp_protocol, typename ITCP_protocol<Client>::Game_param *param);
    void	start_game(ITCP_protocol<Client> &itcp_protocol);
    void	ready_game(ITCP_protocol<Client> &itcp_protocol, bool ready);
private:
    bool	m_is_start;
    bool    m_is_running;
    ITCP_protocol<Client>::Callback	*m_turn;
    static uintmax_t const	m_size = 19;
    std::array<ITCP_protocol<Client>::Game_stone::Color, m_size * m_size>	m_board;
    std::string	*m_name;
    Black	m_black;
    White   m_white;
    ITime   *m_timeout;
private:
    std::list<ITCP_protocol<Client> *>	m_itcp_protocols;
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
    Game_exception_client_transfer(ITCP_protocol<Client> *client) noexcept;
    Game_exception_client_transfer(Game_exception_client_transfer const &) noexcept;
    ~Game_exception_client_transfer(void) noexcept;
    char const  *what(void) const noexcept;
    Game_exception_client_transfer    &operator=(Game_exception_client_transfer const &) noexcept;
public:
    ITCP_protocol<Client>    *m_client;
};

#endif		/* !GAME_HPP_ */
