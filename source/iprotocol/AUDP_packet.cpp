//
// AUDP_packet.cpp for AUDP_packet in /home/plasko_a/projet/cplusplus/rtype/source/iprotocol
// 
// Made by Antoine Plaskowski
// Login   <antoine.plaskowski@epitech.eu>
// 
// Started on  Sun Dec  6 04:04:29 2015 Antoine Plaskowski
// Last update Tue Dec 22 16:05:35 2015 Antoine Plaskowski
//

#include	"AUDP_packet.hpp"

AUDP_packet::AUDP_packet(void) :
  m_packet({})
{
}

AUDP_packet::~AUDP_packet(void)
{
}

AUDP_packet::Opcode	AUDP_packet::get_opcode(void) const
{
  return (m_packet.opcode);
}

void	AUDP_packet::set_size(uint16_t size)
{
  m_packet.size = size;
}

uintmax_t	AUDP_packet::get_size(void) const
{
  return (m_packet.size);
}

uint8_t	AUDP_packet::operator[](uint16_t idx) const
{
  return (m_packet.data[idx]);
}
