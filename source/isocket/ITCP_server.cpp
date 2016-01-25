//
// ITCP_server.cpp for ITCP_server in /home/plasko_a/projet/cplusplus/rtype
// 
// Made by Antoine Plaskowski
// Login   <antoine.plaskowski@epitech.eu>
// 
// Started on  Fri Nov 20 07:15:58 2015 Antoine Plaskowski
// Last update Thu Dec 10 16:27:50 2015 Antoine Plaskowski
//

#include	"ITCP_server.hpp"

ITCP_server::~ITCP_server(void)
{
}

ITCP_server_exception::~ITCP_server_exception(void) noexcept
{
}

ITCP_server_exception::ITCP_server_exception(void) noexcept
{
}

ITCP_server_exception::ITCP_server_exception(ITCP_server_exception const &) noexcept :
ISocket_exception()
{
}

ITCP_server_exception	&ITCP_server_exception::operator=(ITCP_server_exception const &) noexcept
{
  return (*this);
}

