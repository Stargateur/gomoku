#include    "Player.hpp"

Player::Player(typename iprotocol::ITCP_protocol<Client>::Callback &callback) :
    ACallback(callback),
    m_is_ready(false)
{
}

Player::~Player(void)
{
}

bool    Player::is_ready(void) const
{
    return (m_is_ready);
}

void    Player::game_ready(iprotocol::ITCP_protocol<Client> &, bool ready)
{
    m_is_ready = ready;
}
