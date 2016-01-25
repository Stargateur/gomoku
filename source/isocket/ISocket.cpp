//
// ISocket.cpp for ISocket in /home/plasko_a/projet/cplusplus/rtype/src/server
// 
// Made by Antoine Plaskowski
// Login   <antoine.plaskowski@epitech.eu>
// 
// Started on  Fri Nov 20 04:44:43 2015 Antoine Plaskowski
// Last update Thu Dec 10 02:15:57 2015 Antoine Plaskowski
//

#include	"ISocket.hpp"

ISocket::~ISocket(void)
{
}

ISocket_exception::ISocket_exception(void) noexcept
{
}

ISocket_exception::ISocket_exception(ISocket_exception const &) noexcept
{
}

ISocket_exception::~ISocket_exception(void) noexcept
{
}

ISocket_exception     &ISocket_exception::operator=(ISocket_exception const &) noexcept
{
  return (*this);
}

