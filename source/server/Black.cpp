#include	"Black.hpp"

Black::Black(typename iprotocol::ITCP_protocol<Client>::Callback &callback) :
    Player(callback)
{
}

Black::~Black(void)
{
}

void	Black::game_stone_put(iprotocol::ITCP_protocol<Client> &itcp_protocol, iprotocol::Game_stone *stone)
{
    stone->color = iprotocol::Game_stone::Color::Black;
    m_callback.game_stone_put(itcp_protocol, stone);
}