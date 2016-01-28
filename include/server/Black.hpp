//
// Black.hpp for Black in /home/plasko_a/projet/gomoku
//
// Made by Antoine Plaskowski
// Login   <antoine.plaskowski@epitech.eu>
//
// Started on  Wed Jan 27 14:45:21 2016 Antoine Plaskowski
// Last update Thu Jan 28 10:25:06 2016 Antoine Plaskowski
//

#ifndef		BLACK_HPP_
# define	BLACK_HPP_

# include	<array>
# include	"Client.hpp"
# include	"ACallback.hpp"

class	Black : public ACallback<Client>
{
public:
    Black(typename ITCP_protocol<Client>::Callback &callback);
    ~Black(void);
    void	run(void);
    bool	is_ready(void) const;
    void	put_stone_game(ITCP_protocol<Client> &itcp_protocol, typename ITCP_protocol<Client>::Game_stone *stone);
    void	ready_game(ITCP_protocol<Client> &itcp_protocol, bool ready);
private:
    bool	m_is_ready;
};

#endif		/* !BLACK_HPP_ */
