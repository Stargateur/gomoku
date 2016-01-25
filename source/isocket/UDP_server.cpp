//
// UDP_server.cpp for UDP_server in /home/plasko_a/projet/cplusplus/rtype
// 
// Made by Antoine Plaskowski
// Login   <antoine.plaskowski@epitech.eu>
// 
// Started on  Fri Nov 20 07:53:57 2015 Antoine Plaskowski
// Last update Tue Dec  8 15:38:03 2015 Antoine Plaskowski
//

#ifdef		_WIN32
# include <io.h>
# define	SHUT_RDWR SD_BOTH
typedef long ssize_t;
#else
# include	<unistd.h>
# include	<arpa/inet.h>
#endif
#include	<iostream>
#include	<cstring>
#include	"UDP_server.hpp"
#include	"UDP_client.hpp"

UDP_server::UDP_server(std::string const &port) :
  ASocket(socket(port)),
  m_port(port)
{
}

UDP_server::~UDP_server(void)
{
  ::shutdown(m_fd, SHUT_RDWR);
#ifdef	_WIN32
	WSACleanup();
#endif
}

int	UDP_server::aux_socket(struct addrinfo const *rp)
{
  int   fd;

  if (rp == NULL)
    throw UDP_server_exception(strerror(errno));
  if ((fd = ::socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol)) == -1)
    return (aux_socket(rp->ai_next));
  if (::bind(fd, rp->ai_addr, rp->ai_addrlen) == -1)
    {
      close(fd);
      return (aux_socket(rp->ai_next));
    }
  return (fd);
}

int	UDP_server::socket(std::string const &port)
{
  struct addrinfo const	hints =
    {
      AI_PASSIVE,
      AF_UNSPEC,
      SOCK_DGRAM,
      IPPROTO_UDP,
      0,
      NULL,
      NULL,
      NULL
    };
  struct addrinfo	*result;
  int   status = ::getaddrinfo(NULL, port.c_str(), &hints, &result);
  if (status != 0)
    throw UDP_server_exception(gai_strerror(status));
#ifdef	_WIN32
	WSAStartup(MAKEWORD(2, 2), NULL);
#endif
  int	fd = aux_socket(result);
  ::freeaddrinfo(result);
  return (fd);
}

uintmax_t	UDP_server::recvfrom(uint8_t &data, uintmax_t size, IUDP_server::u_sockaddr &sockaddr, socklen_t &len) const
{
  len = sizeof(sockaddr);
  std::memset(&sockaddr.base, 0, len);
  ssize_t   ret(::recvfrom(m_fd, reinterpret_cast<char *>(&data), size, 0, &sockaddr.base, &len));
  if (ret == -1)
    throw UDP_server_exception(strerror(errno));
  return (static_cast<size_t>(ret));
}

uintmax_t	UDP_server::sendto(uint8_t const &data, uintmax_t size, IUDP_server::u_sockaddr const &sockaddr, socklen_t len) const
{
  ssize_t   ret(::sendto(m_fd, reinterpret_cast<const char *>(&data), size, 0, &sockaddr.base, len));
  if (ret == -1)
    throw UDP_server_exception(strerror(errno));
  return (static_cast<size_t>(ret));
}

UDP_server_exception::UDP_server_exception(char const *what) :
  m_what(what)
{
}

char const	*UDP_server_exception::what(void) const noexcept
{
  return (m_what);
}
