#include	"Black.hpp"

Black::Black(typename iprotocol::ITCP_protocol<Client>::Callback &callback, Board &board) :
    Player(callback, board)
{
}

Black::~Black(void)
{
}

void	Black::game_stone_put(iprotocol::ITCP_protocol<Client> &itcp_protocol, iprotocol::Game_stone *stone)
{
    stone->color = iprotocol::Game_stone::Color::Black;
    Player::game_stone_put(itcp_protocol, stone);
}