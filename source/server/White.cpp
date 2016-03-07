#include	"White.hpp"

White::White(typename iprotocol::ITCP_protocol<Client>::Callback &callback) :
    Player(callback)
{
}

White::~White(void)
{
}

void	White::game_stone_put(iprotocol::ITCP_protocol<Client> &itcp_protocol, iprotocol::Game_stone *stone)
{
    stone->color = iprotocol::Game_stone::Color::White;
    m_callback.game_stone_put(itcp_protocol, stone);
}
