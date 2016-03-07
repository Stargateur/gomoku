#include    "Player.hpp"

Player::Player(typename iprotocol::ITCP_protocol<Client>::Callback &callback, Board &board) :
    ACallback(callback),
    m_is_ready(false),
    m_board(board)
{
}

Player::~Player(void)
{
}

bool    Player::is_ready(void) const
{
    return (m_is_ready);
}

void    Player::game_stone_put(iprotocol::ITCP_protocol<Client> &itcp_protocol, iprotocol::Game_stone *stone)
{
    
}

void    Player::game_ready(iprotocol::ITCP_protocol<Client> &, bool ready)
{
    m_is_ready = ready;
}
