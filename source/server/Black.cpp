#include	"Black.hpp"

Black::Black(typename iprotocol::ITCP_protocol<Client>::Callback &callback) :
    ACallback(callback),
    m_is_ready(false)
{
}

Black::~Black(void)
{
}

bool	Black::is_ready(void) const
{
    return (m_is_ready);
}

void	Black::game_stone_put(iprotocol::ITCP_protocol<Client> &itcp_protocol, iprotocol::Game_stone *stone)
{
    stone->color = iprotocol::Game_stone::Color::Black;
    m_callback.game_stone_put(itcp_protocol, stone);
}

void	Black::game_ready(iprotocol::ITCP_protocol<Client> &, bool ready)
{
    m_is_ready = ready;
}
