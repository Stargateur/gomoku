//
// IUDP_server.hpp for IUDP_server in /home/plasko_a/projet/cplusplus/rtype/include/server
// 
// Made by Antoine Plaskowski
// Login   <antoine.plaskowski@epitech.eu>
// 
// Started on  Fri Nov 20 05:00:20 2015 Antoine Plaskowski
// Last update Thu Dec 10 02:22:09 2015 Antoine Plaskowski
//

#ifndef		IUDP_SERVER_HPP_
# define	IUDP_SERVER_HPP_

# include	<cstdint>
# include	<string>
# ifdef		_WIN32
#  include <WinSock2.h>
#  include <WS2tcpip.h>
#  define _WINSOCK2API_
#  define _WINSOCKAPI_
# endif
# include	"ASocket.hpp"

class	IUDP_server;

# include	"IUDP_client.hpp"

class	IUDP_server : virtual public ISocket
{
public:
  union u_sockaddr
  {
    struct sockaddr     base;
    struct sockaddr_in  ipv4;
    struct sockaddr_in6 ipv6;
  };
public:
  virtual	~IUDP_server(void);
  virtual uintmax_t	recvfrom(uint8_t &data, uintmax_t size, u_sockaddr &sockaddr, socklen_t &len) const = 0;
  virtual uintmax_t	sendto(uint8_t const &data, uintmax_t size, u_sockaddr const &sockaddr, socklen_t const len) const = 0;
};

class	IUDP_server_exception : public ISocket_exception
{
public:
  IUDP_server_exception(void) noexcept;
  IUDP_server_exception(IUDP_server_exception const &) noexcept;
  virtual ~IUDP_server_exception(void) noexcept;
  IUDP_server_exception	&operator=(IUDP_server_exception const &) noexcept;
};

#endif		/* !IUDP_SERVER_HPP_ */
