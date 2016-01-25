//
// UDP_packet_send.cpp for UDP_packet_send in /home/plasko_a/projet/cplusplus/rtype/source/iprotocol
// 
// Made by Antoine Plaskowski
// Login   <antoine.plaskowski@epitech.eu>
// 
// Started on  Sun Dec  6 04:07:41 2015 Antoine Plaskowski
// Last update Tue Dec 22 21:03:16 2015 Antoine Plaskowski
//

#include	<iostream>
#include	"UDP_packet_send.hpp"

UDP_packet_send::UDP_packet_send(void) :
  AUDP_packet()
{
}

UDP_packet_send::~UDP_packet_send(void)
{
}

void	UDP_packet_send::send(IUDP_client const &socket)
{
  uintmax_t	ret = socket.send(m_buffer[0], m_size_header + get_size());

  if (ret == 0)
    throw std::exception();
  if (ret < m_size_header + get_size())
    throw std::exception();
  set_size(0);
}

void	UDP_packet_send::sendto(IUDP_server const &socket, IUDP_server::u_sockaddr &sockaddr, socklen_t &len)
{
  uintmax_t	ret = socket.sendto(m_buffer[0], m_size_header + get_size(), sockaddr, len);

  if (ret == 0)
    throw std::exception();
  if (ret < m_size_header + get_size())
    throw std::exception();
  set_size(0);
}

void	UDP_packet_send::put(std::string const &string)
{
  put(static_cast<uint8_t>(string.size()));
  for (uintmax_t i = 0; i < string.size() && i < UINT8_MAX; i++)
    put(static_cast<uint8_t>(string[i]));
}

void	UDP_packet_send::set_opcode(Opcode opcode)
{
  m_packet.opcode = opcode;
}
