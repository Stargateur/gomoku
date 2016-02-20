//
// White.hpp for White in /home/plasko_a/projet/gomoku
//
// Made by Antoine Plaskowski
// Login   <antoine.plaskowski@epitech.eu>
//
// Started on  Wed Jan 27 14:45:21 2016 Antoine Plaskowski
// Last update Thu Jan 28 10:25:53 2016 Antoine Plaskowski
//

#ifndef		WHITE_HPP_
# define	WHITE_HPP_

# include	<array>
# include	"Client.hpp"
# include	"ACallback.hpp"

class	White : public ACallback<Client>
{
public:
    White(typename iprotocol::ITCP_protocol<Client>::Callback &callback);
    ~White(void);
    void	run(void);
    bool	is_ready(void) const;
    void	put_stone_game(iprotocol::ITCP_protocol<Client> &itcp_protocol, iprotocol::Game_stone *stone);
    void	ready_game(iprotocol::ITCP_protocol<Client> &itcp_protocol, bool ready);
private:
    bool	m_is_ready;
};

#endif		/* !WHITE_HPP_ */
