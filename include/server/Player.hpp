#ifndef     Player_HPP_
# define    Player_HPP_

# include   <array>
# include   "Client.hpp"
# include   "ACallback.hpp"

class   Player : public iprotocol::ACallback<Client>
{
public:
    Player(typename iprotocol::ITCP_protocol<Client>::Callback &callback);
    ~Player(void);
    void    run(void);
    bool    is_ready(void) const;
    void    game_ready(iprotocol::ITCP_protocol<Client> &itcp_protocol, bool ready);
private:
    bool    m_is_ready;
};

#endif      /* !Player_HPP_ */
