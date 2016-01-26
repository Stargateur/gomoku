//
// ATCP_packet.cpp for ATCP_packet in /home/plasko_a/projet/cplusplus/rtype/source/iprotocol
// 
// Made by Antoine Plaskowski
// Login   <antoine.plaskowski@epitech.eu>
// 
// Started on  Sun Dec  6 04:04:29 2015 Antoine Plaskowski
// Last update Tue Jan 26 00:48:47 2016 Antoine Plaskowski
//

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
    case ATCP_packet::Game_create:
      return ("Create_game");
    case ATCP_packet::Game_delete:
      return ("Game_delete");
    case ATCP_packet::Player_joined:
      return ("Player_joined");
    case ATCP_packet::Message:
      return ("Message");
    case ATCP_packet::Start_game:
      return ("Start_game");
    case ATCP_packet::Ready_game:
      return ("Ready_game");
    case ATCP_packet::Result_game:
      return ("Result_game");
    }
  throw std::exception();
}

std::ostream	&operator<<(std::ostream &os, ATCP_packet::Opcode opcode)
{
  return (os << ATCP_packet::get_str_opcode(opcode));
}
