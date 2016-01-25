//
// UDP_packet_recv.cpp for UDP_packet_recv in /home/plasko_a/projet/cplusplus/rtype/source/iprotocol
// 
// Made by Antoine Plaskowski
// Login   <antoine.plaskowski@epitech.eu>
// 
// Started on  Sun Dec  6 04:05:19 2015 Antoine Plaskowski
// Last update Tue Dec 22 19:39:26 2015 Antoine Plaskowski
//

#include	<iostream>
#include	"UDP_packet_recv.hpp"

UDP_packet_recv::UDP_packet_recv(void) :
  AUDP_packet()
{
}

UDP_packet_recv::~UDP_packet_recv(void)
{
}

void	UDP_packet_recv::recv(IUDP_client const &socket)
{
  uintmax_t	ret;
  ret = socket.recv(m_buffer[0], sizeof(m_buffer));
  if (ret == 0)
    throw std::exception();
  if (ret < m_size_header)
    throw std::exception();
  if (ret < m_size_header + get_size())
    throw std::exception();
  set_size(0);
}

void	UDP_packet_recv::recvfrom(IUDP_server const &socket, IUDP_server::u_sockaddr &sockaddr, socklen_t &len)
{
  uintmax_t	ret;
  ret = socket.recvfrom(m_buffer[0], sizeof(m_buffer), sockaddr, len);
  if (ret == 0)
    throw std::exception();
  if (ret < m_size_header)
    throw std::exception();
  if (ret < m_size_header + get_size())
    throw std::exception();
  set_size(0);
}
  
void	UDP_packet_recv::get(std::string &string)
{
  uint8_t	size;

  get(size);
  for (uintmax_t i = 0; i < size; i++)
    {
      uint8_t   c;
      get(c);
      string.push_back(static_cast<char>(c));
    }
}
