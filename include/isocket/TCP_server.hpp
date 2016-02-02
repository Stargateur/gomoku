//
// TCP_server.hpp for TCP_server in /home/plasko_a/projet/cplusplus/rtype/include/server
//
// Made by Antoine Plaskowski
// Login   <antoine.plaskowski@epitech.eu>
//
// Started on  Fri Nov 20 05:16:07 2015 Antoine Plaskowski
// Last update Tue Dec  8 15:29:57 2015 Antoine Plaskowski
//

#ifndef		TCP_SERVER_HPP_
# define	TCP_SERVER_HPP_

# include	<string>
# ifdef	_WIN32
#define _WIN32_WINNT 0xA000
#define WIN32_LEAN_AND_MEAN
#include <WinSock2.h>
#include <WS2tcpip.h>
# else
#  include	<unistd.h>
#  include	<sys/socket.h>
#  include	<netdb.h>
# endif
# include	"ITCP_server.hpp"

class TCP_server : public ASocket, public ITCP_server
{
public:
    TCP_server(std::string const &port);
    ~TCP_server(void);
    ITCP_client	&accept(void) const;
private:
    static int	aux_bind(struct addrinfo const *rp);
    static int	bind(std::string const &port);
};

class	TCP_server_exception : public ITCP_server_exception
{
public:
    TCP_server_exception(char const *what);
    TCP_server_exception(std::string const &&what) noexcept;
    char const	*what(void) const noexcept;
private:
    std::string const m_what;
};

#endif		/* !TCP_SERVER_HPP_ */
