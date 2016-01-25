//
// TCP_packet_recv.cpp for TCP_packet_recv in /home/plasko_a/projet/cplusplus/rtype/source/iprotocol
// 
// Made by Antoine Plaskowski
// Login   <antoine.plaskowski@epitech.eu>
// 
// Started on  Sun Dec  6 04:05:19 2015 Antoine Plaskowski
// Last update Tue Dec 22 17:07:05 2015 Antoine Plaskowski
//

#include	<iostream>
#include	"TCP_packet_recv.hpp"

TCP_packet_recv::TCP_packet_recv(void) :
  ATCP_packet(),
  m_recv(0)
{
}

TCP_packet_recv::~TCP_packet_recv(void)
{
}

bool	TCP_packet_recv::recv(ITCP_client const &socket)
{
  if (m_recv >= sizeof(m_buffer))
    throw std::exception();
  uintmax_t	ret;
  if (m_recv < m_size_header)
    ret = socket.recv(m_buffer[m_recv], m_size_header - m_recv);
  else
    ret = socket.recv(m_buffer[m_recv], m_size_header + get_size() - m_recv);
  if (ret == 0)
    throw std::exception();
  m_recv += ret;
  if (m_recv < m_size_header)
    return (false);
  if (m_recv < m_size_header + get_size())
    return (false);
  set_size(0);
  m_recv = 0;
  return (true);
}

void	TCP_packet_recv::get(std::string &string)
{
  uint8_t       size;

  get(size);
  for (uintmax_t i = 0; i < size; i++)
    {
      uint8_t   c;
      get(c);
      string.push_back(static_cast<char>(c));
    }
}
