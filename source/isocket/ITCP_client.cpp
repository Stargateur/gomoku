//
// ITCP_client.cpp for ITCP_client in /home/plasko_a/projet/cplusplus/rtype
// 
// Made by Antoine Plaskowski
// Login   <antoine.plaskowski@epitech.eu>
// 
// Started on  Fri Nov 20 06:46:37 2015 Antoine Plaskowski
// Last update Thu Dec 10 16:26:49 2015 Antoine Plaskowski
//

#include	"ITCP_client.hpp"

ITCP_client::~ITCP_client(void)
{
}

ITCP_client_exception::ITCP_client_exception(void) noexcept
{
}

ITCP_client_exception::ITCP_client_exception(ITCP_client_exception const &) noexcept :
ISocket_exception()
{
}

ITCP_client_exception::~ITCP_client_exception(void) noexcept
{
}

ITCP_client_exception	&ITCP_client_exception::operator=(ITCP_client_exception const &) noexcept
{
  return (*this);
}
