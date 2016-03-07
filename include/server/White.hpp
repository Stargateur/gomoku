#ifndef		WHITE_HPP_
# define	WHITE_HPP_

# include   "Player.hpp"

class	White : public Player
{
public:
    White(typename iprotocol::ITCP_protocol<Client>::Callback &callback, Board &board);
    ~White(void);
    void	game_stone_put(iprotocol::ITCP_protocol<Client> &itcp_protocol, iprotocol::Game_stone *stone);
};

#endif		/* !WHITE_HPP_ */
