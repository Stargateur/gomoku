//
// UDP_server.hpp for UDP_server in /home/plasko_a/projet/cplusplus/rtype/include/server
// 
// Made by Antoine Plaskowski
// Login   <antoine.plaskowski@epitech.eu>
// 
// Started on  Fri Nov 20 05:11:04 2015 Antoine Plaskowski
// Last update Tue Dec  8 15:36:11 2015 Antoine Plaskowski
//

#ifndef		UDP_SERVER_HPP_
# define	UDP_SERVER_HPP_

# include	<string>
# ifndef	_WIN32
#  include	<sys/socket.h>
#  include	<netdb.h>
# endif
# include	"IUDP_server.hpp"

class	UDP_server : public IUDP_server, public ASocket
{
public:
  UDP_server(std::string const &port);
  ~UDP_server(void);
  uintmax_t	recvfrom(uint8_t &data, uintmax_t size, IUDP_server::u_sockaddr &sockaddr, socklen_t &len) const;
  uintmax_t	sendto(uint8_t const &data, uintmax_t size, IUDP_server::u_sockaddr const &sockaddr, socklen_t len) const;
private:
  static int	aux_socket(struct addrinfo const *rp);
  static int	socket(std::string const &port);
private:
  std::string const	m_port;
};

class	UDP_server_exception : public IUDP_server_exception
{
public:
  UDP_server_exception(char const *what);
  char const	*what(void) const noexcept;
private:
  char const	*m_what;
};

#endif		/* !UDP_SERVER_HPP_ */
