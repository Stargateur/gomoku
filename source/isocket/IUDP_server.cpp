//
// IUDP_server.cpp for IUDP_server in /home/plasko_a/projet/cplusplus/rtype
// 
// Made by Antoine Plaskowski
// Login   <antoine.plaskowski@epitech.eu>
// 
// Started on  Fri Nov 20 07:53:25 2015 Antoine Plaskowski
// Last update Thu Dec 10 16:28:37 2015 Antoine Plaskowski
//

#include	"IUDP_server.hpp"

IUDP_server::~IUDP_server(void)
{
}

IUDP_server_exception::IUDP_server_exception(void) noexcept
{
}

IUDP_server_exception::IUDP_server_exception(IUDP_server_exception const &) noexcept :
ISocket_exception()
{
}

IUDP_server_exception::~IUDP_server_exception(void) noexcept
{
}

IUDP_server_exception	&IUDP_server_exception::operator=(IUDP_server_exception const &) noexcept
{
  return (*this);
}

