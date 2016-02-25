#include	"White.hpp"

White::White(typename iprotocol::ITCP_protocol<Client>::Callback &callback) :
    ACallback(callback),
    m_is_ready(false)
{
}

White::~White(void)
{
}

bool	White::is_ready(void) const
{
    return (m_is_ready);
}

void	White::put_stone_game(iprotocol::ITCP_protocol<Client> &itcp_protocol, iprotocol::Game_stone *stone)
{
    stone->color = iprotocol::Game_stone::Color::White;
    m_callback.put_stone_game(itcp_protocol, stone);
}

void	White::ready_game(iprotocol::ITCP_protocol<Client> &, bool ready)
{
    m_is_ready = ready;
}
