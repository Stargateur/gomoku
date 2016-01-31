//
// ATCP_packet.cpp for ATCP_packet in /home/plasko_a/projet/cplusplus/rtype/source/iprotocol
//
// Made by Antoine Plaskowski
// Login   <antoine.plaskowski@epitech.eu>
//
// Started on  Sun Dec  6 04:04:29 2015 Antoine Plaskowski
// Last update Tue Jan 26 13:08:33 2016 Antoine Plaskowski
//

#include    <stdexcept>>
#include	"ATCP_packet.hpp"

ATCP_packet::ATCP_packet(void) :
    m_packet({})
{
}

ATCP_packet::~ATCP_packet(void)
{
}

ATCP_packet::Opcode	ATCP_packet::get_opcode(void) const
{
    return (m_packet.opcode);
}

void	ATCP_packet::set_size(uint16_t size)
{
    m_packet.size = size;
}

uintmax_t	ATCP_packet::get_size(void) const
{
    return (m_packet.size);
}

uint8_t	ATCP_packet::operator[](uint16_t idx) const
{
    return (m_packet.data[idx]);
}

char const	*ATCP_packet::get_str_opcode(ATCP_packet::Opcode opcode)
{
    switch (opcode)
    {
    case ATCP_packet::Result:
        return ("Result");
    case ATCP_packet::Connect:
        return ("Connect");
    case ATCP_packet::Disconnect:
        return ("Disconnect");
    case ATCP_packet::Ping:
        return ("Ping");
    case ATCP_packet::Pong:
        return ("Pong");
    case ATCP_packet::Create_game:
        return ("Create_game");
    case ATCP_packet::Join_game:
        return ("Join_game");
    case ATCP_packet::Leave_game:
        return ("Leave_game");
    case ATCP_packet::Put_stone_game:
        return ("Put_stone_game");
    case ATCP_packet::Change_param_game:
        return ("Change_param_game");
    case ATCP_packet::List_param_game:
        return ("List_Param_game");
    case ATCP_packet::Game_created:
        return ("Game_created");
    case ATCP_packet::Game_player_joined:
        return ("Game_player_joined");
    case ATCP_packet::Game_player_left:
        return ("Game_player_left");
    case ATCP_packet::Game_param_changed:
        return ("Game_param_changed");
    case ATCP_packet::Game_stone_put:
        return ("Game_stone_put");
    case ATCP_packet::Game_deleted:
        return ("Game_deleted");
    case ATCP_packet::Start_game:
        return ("Start_game");
    case ATCP_packet::Ready_game:
        return ("Ready_game");
    case ATCP_packet::Result_game:
        return ("Result_game");
    case ATCP_packet::Message:
        return ("Message");
    }
    throw std::logic_error("Unknow Opcode");
}

std::ostream	&operator<<(std::ostream &os, ATCP_packet::Opcode opcode)
{
    return (os << ATCP_packet::get_str_opcode(opcode));
}

ATCP_packet_exception::~ATCP_packet_exception(void) noexcept
{
}

ATCP_packet_exception::ATCP_packet_exception(void) noexcept
{
}

ATCP_packet_exception::ATCP_packet_exception(ATCP_packet_exception const &) noexcept
{
}

ATCP_packet_exception   &ATCP_packet_exception::operator=(ATCP_packet_exception const &) noexcept
{
    return (*this);
}

char const  *ATCP_packet_exception::what(void) const noexcept
{
    return ("ATCP_packet_exception");
}