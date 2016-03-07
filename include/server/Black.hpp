#ifndef		BLACK_HPP_
# define	BLACK_HPP_

# include   "Player.hpp"

class	Black : public Player
{
public:
    Black(typename iprotocol::ITCP_protocol<Client>::Callback &callback, Board &board);
    ~Black(void);
    void	game_stone_put(iprotocol::ITCP_protocol<Client> &itcp_protocol, iprotocol::Game_stone *stone);
};

#endif		/* !BLACK_HPP_ */
