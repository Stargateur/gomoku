//
// TCP_server.cpp for TCP_server in /home/plasko_a/projet/cplusplus/rtype
// 
// Made by Antoine Plaskowski
// Login   <antoine.plaskowski@epitech.eu>
// 
// Started on  Fri Nov 20 07:15:53 2015 Antoine Plaskowski
// Last update Tue Dec  8 15:34:37 2015 Antoine Plaskowski
//

#include	<iostream>
#ifdef		_WIN32
# include <io.h>
# include <WinSock2.h>
# include <WS2tcpip.h>
#else
# include	<unistd.h>
#endif
#include	<cstring>
#include	"TCP_server.hpp"
#include	"TCP_client.hpp"

TCP_server::TCP_server(std::string const &port) : ASocket(bind(port))
{
}

TCP_server::~TCP_server(void)
{
#ifdef	_WIN32
	WSACleanup();
#endif
  close(m_fd);
}

int	TCP_server::aux_bind(struct addrinfo const *rp)
{
  if (rp == NULL)
    throw TCP_server_exception(strerror(errno));
  int	fd = ::socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
  if (fd == -1)
    return (aux_bind(rp->ai_next));
  if (::bind(fd, rp->ai_addr, rp->ai_addrlen) != 0)
    {
      ::close(fd);
      return (aux_bind(rp->ai_next));
    }
  if (::listen(fd, 42) != 0)
    {
      ::close(fd);
      return (aux_bind(rp->ai_next));
    }
  return (fd);
}

int	TCP_server::bind(std::string const &port)
{
  struct addrinfo const	hints =
    {
      AI_PASSIVE,
      AF_UNSPEC,
      SOCK_STREAM,
      IPPROTO_TCP,
      0,
      NULL,
      NULL,
      NULL
    };
  struct addrinfo	*result;
  int	status = ::getaddrinfo(NULL, port.c_str(), &hints, &result);
  if (status != 0)
    throw TCP_server_exception(gai_strerror(status));
#ifdef	_WIN32
	WSAStartup(MAKEWORD(2, 2), NULL);
#endif
  int	fd = aux_bind(result);
  ::freeaddrinfo(result);
  return (fd);
}

ITCP_client	&TCP_server::accept(void) const
{
  return (*new TCP_client(*this));
}

TCP_server_exception::TCP_server_exception(char const *what) :
  m_what(what)
{
}

char const	*TCP_server_exception::what(void) const noexcept
{
  return (m_what);
}
