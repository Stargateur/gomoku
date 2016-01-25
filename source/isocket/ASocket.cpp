//
// ASocket.cpp for ASocket in /home/plasko_a/projet/cplusplus/rtype
// 
// Made by Antoine Plaskowski
// Login   <antoine.plaskowski@epitech.eu>
// 
// Started on  Fri Nov 20 05:43:34 2015 Antoine Plaskowski
// Last update Thu Dec 10 16:36:04 2015 Antoine Plaskowski
//

#include	<algorithm>
#include	<exception>
#include	<cstring>
#include	<fcntl.h>
#include	"ASocket.hpp"

ASocket::ASocket(int fd) : m_fd(fd)
{
#ifndef			_WIN32
  if (fcntl(m_fd, F_GETFD) == -1)
    throw ASocket_exception(strerror(errno));
#endif
}

ASocket::~ASocket(void)
{
}

int	ASocket::get_fd(void) const
{
  return (m_fd);
}

ASocket_exception::ASocket_exception(char const *what) :
  m_what(what)
{
}

ASocket_exception::ASocket_exception(ASocket_exception const &asocket_exception) noexcept :
ISocket_exception(),
  m_what(asocket_exception.m_what)
{
}

ASocket_exception::~ASocket_exception(void) noexcept
{
}

ASocket_exception &ASocket_exception::operator=(ASocket_exception const &asocket_exception) noexcept
{
  m_what = asocket_exception.m_what;
  return (*this);
}

char const	*ASocket_exception::what(void) const noexcept
{
  return (m_what);
}
