//
// Select.cpp for Select in /home/plasko_a/projet/cplusplus/rtype/source/isocket
// 
// Made by Antoine Plaskowski
// Login   <antoine.plaskowski@epitech.eu>
// 
// Started on  Tue Dec  8 14:01:13 2015 Antoine Plaskowski
// Last update Tue Dec  8 15:50:57 2015 Antoine Plaskowski
//

#include	<algorithm>
#include	<cstring>
#include	<cerrno>
#include	"Select.hpp"

Select::Select(void) :
  m_readfds({}),
  m_writefds({}),
  m_nfds(-1)
{
}

void	Select::reset(void)
{
  FD_ZERO(&m_readfds);
  FD_ZERO(&m_writefds);
  m_nfds = -1;
}

bool    Select::can_read(ISocket const &socket) const
{
  if (socket.get_fd() >= FD_SETSIZE)
    throw Select_exception(strerror(EDOM));
  return (FD_ISSET(socket.get_fd(), &m_readfds));
}

bool    Select::can_write(ISocket const &socket) const
{
  if (socket.get_fd() >= FD_SETSIZE)
    throw Select_exception(strerror(EDOM));
  return (FD_ISSET(socket.get_fd(), &m_writefds));
}

void    Select::want_read(ISocket const &socket)
{
  if (socket.get_fd() >= FD_SETSIZE)
    throw Select_exception(strerror(EDOM));
  FD_SET(socket.get_fd(), &m_readfds);
  m_nfds = std::max<int>(m_nfds, socket.get_fd());
}

void    Select::want_write(ISocket const &socket)
{
  if (socket.get_fd() >= FD_SETSIZE)
    throw Select_exception(strerror(EDOM));
  FD_SET(socket.get_fd(), &m_writefds);
  m_nfds = std::max<int>(m_nfds, socket.get_fd());
}

void    Select::select(ITime const *timeout)
{
  int   ret;

  if (timeout == nullptr)
#ifdef		_WIN32
    ret = ::select(m_nfds + 1, &m_readfds, &m_writefds, NULL, NULL);
#else
    ret = pselect(m_nfds + 1, &m_readfds, &m_writefds, NULL, NULL, NULL);
#endif
  else
    {
#ifdef		_WIN32
      struct timeval   time = { static_cast<long>(timeout->get_second()), static_cast<long>(timeout->get_nano()) * 1000};
	  ret = ::select(m_nfds + 1, &m_readfds, &m_writefds, NULL, &time);
#else
      struct timespec   time = {timeout->get_second(), timeout->get_nano()};
      ret = pselect(m_nfds + 1, &m_readfds, &m_writefds, NULL, &time, NULL);
#endif
    }
  if (ret == -1)
    throw Select_exception(strerror(errno));
}

Select_exception::Select_exception(char const *what) :
  m_what(what)
{
}

char const	*Select_exception::what(void) const noexcept
{
  return (m_what);
}
