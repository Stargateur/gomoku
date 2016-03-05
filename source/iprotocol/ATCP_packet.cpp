#include    <stdexcept>
#include	"ATCP_packet.hpp"

iprotocol::ATCP_packet::ATCP_packet(void) :
    m_packet()
{
    set_size(0);
}

iprotocol::ATCP_packet::~ATCP_packet(void)
{
}

iprotocol::ATCP_packet::Opcode	iprotocol::ATCP_packet::get_opcode(void) const
{
    return (m_packet.opcode);
}

void	iprotocol::ATCP_packet::set_size(uint16_t size)
{
    m_packet.size = size;
}

uintmax_t	iprotocol::ATCP_packet::get_size(void) const
{
    return (m_packet.size);
}

uint8_t	iprotocol::ATCP_packet::operator[](uint16_t idx) const
{
    return (m_packet.data[idx]);
}

char const	*iprotocol::ATCP_packet::get_str_opcode(iprotocol::ATCP_packet::Opcode opcode)
{
    switch (opcode)
    {
    case iprotocol::ATCP_packet::Result:
        return ("Result");
    case iprotocol::ATCP_packet::Connect:
        return ("Connect");
    case iprotocol::ATCP_packet::Disconnect:
        return ("Disconnect");
    case iprotocol::ATCP_packet::Ping:
        return ("Ping");
    case iprotocol::ATCP_packet::Pong:
        return ("Pong");
    case iprotocol::ATCP_packet::Game_create:
        return ("Game_create");
    case iprotocol::ATCP_packet::Game_delete:
        return ("Game_delete");
    case iprotocol::ATCP_packet::Game_join:
        return ("Game_join");
    case iprotocol::ATCP_packet::Game_leave:
        return ("Game_leave");
    case iprotocol::ATCP_packet::Game_param:
        return ("Game_param");
    case iprotocol::ATCP_packet::Game_player_param:
        return ("Game_player_param");
    case iprotocol::ATCP_packet::Game_player_join:
        return ("Game_player_join");
    case iprotocol::ATCP_packet::Game_player_leave:
        return ("Game_player_leave");
    case iprotocol::ATCP_packet::Game_stone_put:
        return ("Game_stone_put");
    case iprotocol::ATCP_packet::Game_start:
        return ("Game_start");
    case iprotocol::ATCP_packet::Game_ready:
        return ("Game_ready");
    case iprotocol::ATCP_packet::Game_score:
        return ("Game_score");
    case iprotocol::ATCP_packet::Game_help:
        return ("Game_help");
    case iprotocol::ATCP_packet::Game_hint:
        return ("Game_hint");
    case iprotocol::ATCP_packet::Game_result:
        return ("Game_result");
    case iprotocol::ATCP_packet::Game_message:
        return ("Game_message");
    }
    throw std::logic_error("Unknow Opcode");
}

std::ostream	&iprotocol::operator<<(std::ostream &os, iprotocol::ATCP_packet::Opcode opcode)
{
    return (os << iprotocol::ATCP_packet::get_str_opcode(opcode));
}

iprotocol::ATCP_packet_exception::~ATCP_packet_exception(void) noexcept
{
}

iprotocol::ATCP_packet_exception::ATCP_packet_exception(void) noexcept
{
}

iprotocol::ATCP_packet_exception::ATCP_packet_exception(iprotocol::ATCP_packet_exception const &) noexcept
{
}

iprotocol::ATCP_packet_exception   &iprotocol::ATCP_packet_exception::operator=(iprotocol::ATCP_packet_exception const &) noexcept
{
    return (*this);
}

char const  *iprotocol::ATCP_packet_exception::what(void) const noexcept
{
    return ("iprotocol_exception");
}