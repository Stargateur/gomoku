//
// ATCP_packet.cpp for ATCP_packet in /home/plasko_a/projet/cplusplus/rtype/source/iprotocol
// 
// Made by Antoine Plaskowski
// Login   <antoine.plaskowski@epitech.eu>
// 
// Started on  Sun Dec  6 04:04:29 2015 Antoine Plaskowski
// Last update Sun Dec 27 18:03:04 2015 Antoine Plaskowski
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
    case ATCP_packet::List_meta_games:
      return ("List_meta_games");
    case ATCP_packet::Meta_games:
      return ("Meta_games");
    case ATCP_packet::Create_game:
      return ("Create_game");
    case ATCP_packet::Join_game:
      return ("Join_game");
    case ATCP_packet::Message:
      return ("Message");
    case ATCP_packet::List_meta_params:
      return ("List_meta_params");
    case ATCP_packet::Meta_params:
      return ("Meta_params");
    case ATCP_packet::Change_param:
      return ("Change_param");
    case ATCP_packet::List_meta_sprites:
      return ("List_meta_sprites");
    case ATCP_packet::Meta_sprites:
      return ("Meta_sprites");
    case ATCP_packet::Take_sprite:
      return ("Take_sprite");
    case ATCP_packet::Give_sprite:
      return ("Give_sprite");
    case ATCP_packet::List_meta_sounds:
      return ("List_meta_sounds");
    case ATCP_packet::Meta_sounds:
      return ("Meta_sounds");
    case ATCP_packet::Take_sound:
      return ("Take_sound");
    case ATCP_packet::Give_sound:
      return ("Give_sound");
    case ATCP_packet::Ready:
      return ("Ready");
    case ATCP_packet::Start:
      return ("Start");
    case ATCP_packet::End:
      return ("End");
    case ATCP_packet::Leave:
      return ("Leave");
    }
}

std::ostream	&operator<<(std::ostream &os, ATCP_packet::Opcode opcode)
{
  return (os << ATCP_packet::get_str_opcode(opcode));
}
