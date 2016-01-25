//
// IUDP_client.hpp for IUDP_client in /home/plasko_a/projet/cplusplus/rtype/include/server
// 
// Made by Antoine Plaskowski
// Login   <antoine.plaskowski@epitech.eu>
// 
// Started on  Fri Nov 20 04:52:54 2015 Antoine Plaskowski
// Last update Thu Dec 10 02:21:46 2015 Antoine Plaskowski
//

#ifndef		IUDP_CLIENT_HPP_
# define	IUDP_CLIENT_HPP_

# include	<string>
# ifdef		_WIN32
#  include	<WinSock2.h>
#  define _WINSOCK2API_
#  define _WINSOCKAPI_
# else
#  include	<sys/socket.h>
#  include	<arpa/inet.h>
# endif

class	IUDP_client;

# include	"ISocket.hpp"
# include	"IUDP_server.hpp"

class	IUDP_client : virtual public ISocket
{
public:
  virtual ~IUDP_client(void);
  virtual uintmax_t	send(uint8_t const &data, uintmax_t size) const = 0;
  virtual uintmax_t	recv(uint8_t &data, uintmax_t size) const = 0;
};

class	IUDP_client_exception : public ISocket_exception
{
public:
  IUDP_client_exception(void) noexcept;
  IUDP_client_exception(IUDP_client_exception const &) noexcept;
  virtual ~IUDP_client_exception(void) noexcept;
  IUDP_client_exception	&operator=(IUDP_client_exception const &) noexcept;
};

#endif		/* !IUDP_CLIENT_HPP_ */
