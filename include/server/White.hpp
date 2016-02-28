#ifndef		WHITE_HPP_
# define	WHITE_HPP_

# include	<array>
# include	"Client.hpp"
# include	"ACallback.hpp"

class	White : public iprotocol::ACallback<Client>
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
