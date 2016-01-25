//
// Standard.cpp for Standard in /home/plasko_a/projet/cplusplus/cpp_spider
// 
// Made by Antoine Plaskowski
// Login   <antoine.plaskowski@epitech.eu>
// 
// Started on  Fri Nov 20 06:01:34 2015 Antoine Plaskowski
// Last update Tue Dec  8 15:41:48 2015 Antoine Plaskowski
//

#ifdef		_WIN32
# include	<io.h>
typedef int ssize_t;
#else
# include	<unistd.h>
#endif
#include	<exception>
#include	<cstring>
#include	<cerrno>
#include	"Standard.hpp"

Standard::Standard(IStandard::io io) : ASocket(io_to_fd(io))
{
}

uintmax_t	Standard::read(uint8_t &data, uintmax_t size) const
{
  ssize_t	ret = ::read(m_fd, &data, size);
  if (ret < 0)
    throw Standard_exception(strerror(errno));
  return (static_cast<uintmax_t>(ret));
}

uintmax_t	Standard::write(uint8_t const &data, uintmax_t size) const
{
  ssize_t	ret = ::write(m_fd, &data, size);
  if (ret < 0)
    throw Standard_exception(strerror(errno));
  return (static_cast<uintmax_t>(ret));
}

int	Standard::io_to_fd(IStandard::io io)
{
  switch (io)
    {
    case IStandard::In:
      return (0);
    case IStandard::Out:
      return (1);
    case IStandard::Err:
      return (2);
    }
  throw Standard_exception("Wrong value of IStandard::io");
}

Standard_exception::Standard_exception(char const *what) :
  m_what(what)
{
}

char const	*Standard_exception::what(void) const noexcept
{
  return (m_what);
}
