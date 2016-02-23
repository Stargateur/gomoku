//
// iprotocol::ATCP_packet.cpp for iprotocol::ATCP_packet in /home/plasko_a/projet/cplusplus/rtype/source/iprotocol
//
// Made by Antoine Plaskowski
// Login   <antoine.plaskowski@epitech.eu>
//
// Started on  Sun Dec  6 04:04:29 2015 Antoine Plaskowski
// Last update Tue Jan 26 13:08:33 2016 Antoine Plaskowski
//

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
    case iprotocol::ATCP_packet::Create_game:
        return ("Create_game");
    case iprotocol::ATCP_packet::Join_game:
        return ("Join_game");
    case iprotocol::ATCP_packet::Leave_game:
        return ("Leave_game");
    case iprotocol::ATCP_packet::Put_stone_game:
        return ("Put_stone_game");
    case iprotocol::ATCP_packet::Change_param_player_game:
        return ("Change_param_player_game");
    case iprotocol::ATCP_packet::Change_param_game:
        return ("Change_param_game");
    case iprotocol::ATCP_packet::List_param_player_game:
        return ("List_Param_player_game");
    case iprotocol::ATCP_packet::List_param_game:
        return ("List_Param_game");
    case iprotocol::ATCP_packet::Game_created:
        return ("Game_created");
    case iprotocol::ATCP_packet::Game_player_joined:
        return ("Game_player_joined");
    case iprotocol::ATCP_packet::Game_player_left:
        return ("Game_player_left");
    case iprotocol::ATCP_packet::Game_player_param_changed:
        return ("Game_player_param_changed");
    case iprotocol::ATCP_packet::Game_param_changed:
        return ("Game_param_changed");
    case iprotocol::ATCP_packet::Game_stone_put:
        return ("Game_stone_put");
    case iprotocol::ATCP_packet::Game_deleted:
        return ("Game_deleted");
    case iprotocol::ATCP_packet::Start_game:
        return ("Start_game");
    case iprotocol::ATCP_packet::Ready_game:
        return ("Ready_game");
    case iprotocol::ATCP_packet::Score_game:
        return ("Score_game");
    case iprotocol::ATCP_packet::Result_game:
        return ("Result_game");
    case iprotocol::ATCP_packet::Message:
        return ("Message");
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