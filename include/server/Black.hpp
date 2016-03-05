#ifndef		BLACK_HPP_
# define	BLACK_HPP_

# include	<array>
# include	"Client.hpp"
# include	"ACallback.hpp"

class	Black : public iprotocol::ACallback<Client>
{
public:
    Black(typename iprotocol::ITCP_protocol<Client>::Callback &callback);
    ~Black(void);
    void	run(void);
    bool	is_ready(void) const;
    void	game_stone_put(iprotocol::ITCP_protocol<Client> &itcp_protocol, iprotocol::Game_stone *stone);
    void	game_ready(iprotocol::ITCP_protocol<Client> &itcp_protocol, bool ready);
private:
    bool	m_is_ready;
};

#endif		/* !BLACK_HPP_ */
