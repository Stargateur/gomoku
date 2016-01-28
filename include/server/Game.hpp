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
# include	"Client.hpp"
# include	"White.hpp"
# include	"Black.hpp"
# include	"ACallback.hpp"

class	Game : public ACallback<Client>
{
public:
    Game(typename ITCP_protocol<Client>::Callback &callback, std::string *name);
    ~Game(void);
    void	run(void);
    std::string const	&get_name(void) const;
    void	create_game(ITCP_protocol<Client> &itcp_protocol, typename ITCP_protocol<Client>::Game *game);
    void	join_game(ITCP_protocol<Client> &itcp_protocol, typename ITCP_protocol<Client>::Game *game);
    void	leave_game(ITCP_protocol<Client> &itcp_protocol);
    void	put_stone_game(ITCP_protocol<Client> &itcp_protocol, typename ITCP_protocol<Client>::Game_stone *stone);
    void	change_param_game(ITCP_protocol<Client> &itcp_protocol, typename ITCP_protocol<Client>::Game_param *param);
    void	list_param_game(ITCP_protocol<Client> &itcp_protocol, std::list<typename ITCP_protocol<Client>::Game_param *> *params);
    void	start_game(ITCP_protocol<Client> &itcp_protocol);
    void	ready_game(ITCP_protocol<Client> &itcp_protocol, bool ready);
private:
    bool	m_is_start;
    ITCP_protocol<Client>::Callback	*m_turn;
    static uintmax_t const	m_size = 19;
    std::array<ITCP_protocol<Client>::Game_stone::Color, m_size * m_size>	m_board;
    std::string	*m_name;
    Black	m_black;
    White m_white;
public:
    std::list<ITCP_protocol<Client> *>	m_itcp_protocols;
};

#endif		/* !GAME_HPP_ */
