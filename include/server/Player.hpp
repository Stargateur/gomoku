#ifndef     Player_HPP_
# define    Player_HPP_

# include   <array>
# include   "Client.hpp"
# include   "ACallback.hpp"
# include   "Board.hpp"

class   Player : public iprotocol::ACallback<Client>
{
public:
    Player(typename iprotocol::ITCP_protocol<Client>::Callback &callback, Board &board);
    ~Player(void);
    void    run(void);
    bool    is_ready(void) const;
    void    game_stone_put(iprotocol::ITCP_protocol<Client> &itcp_protocol, iprotocol::Game_stone *stone);
    void    game_ready(iprotocol::ITCP_protocol<Client> &itcp_protocol, bool ready);
private:
    bool    m_is_ready;
    Board   &m_board;
};

#endif      /* !Player_HPP_ */
