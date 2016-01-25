//
// TCP_packet_send.cpp for TCP_packet_send in /home/plasko_a/projet/cplusplus/rtype/source/iprotocol
// 
// Made by Antoine Plaskowski
// Login   <antoine.plaskowski@epitech.eu>
// 
// Started on  Sun Dec  6 04:07:41 2015 Antoine Plaskowski
// Last update Thu Dec 10 03:47:24 2015 Antoine Plaskowski
//

#include	<iostream>
#include	"TCP_packet_send.hpp"

TCP_packet_send::TCP_packet_send(void) :
  ATCP_packet(),
  m_send(0)
{
}

TCP_packet_send::~TCP_packet_send(void)
{
}

bool	TCP_packet_send::send(ITCP_client const &socket)
{
  if (m_send >= sizeof(m_buffer))
    throw std::exception();
  uintmax_t	ret = socket.send(m_buffer[m_send], m_size_header + get_size() - m_send);

  if (ret == 0)
    throw std::exception();
  m_send += ret;
  if (m_send < m_size_header + get_size())
    return (false);
  m_send = 0;
  set_size(0);
  return (true);
}

void	TCP_packet_send::put(std::string const &string)
{
  put(static_cast<uint8_t>(string.size()));
  for (uintmax_t i = 0; i < string.size() && i < UINT8_MAX; i++)
    put(static_cast<uint8_t>(string[i]));
}

void	TCP_packet_send::set_opcode(Opcode opcode)
{
  m_packet.opcode = opcode;
}
