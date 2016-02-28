#ifndef		TCP_CLIENT_HPP_
# define	TCP_CLIENT_HPP_

# include	<cstdint>
# include	<string>
# ifdef	_WIN32
# define _WIN32_WINNT 0xA000
#define WIN32_LEAN_AND_MEAN
#include <WinSock2.h>
#include <WS2tcpip.h>
# include   <io.h>
#else
# include	<unistd.h>
# include	<arpa/inet.h>
# include	<unistd.h>
#  include	<sys/socket.h>
#  include	<netdb.h>
# endif
# include	"ITCP_client.hpp"
# include	"ITCP_server.hpp"

class	TCP_client : public ASocket, public ITCP_client
{
public:
    TCP_client(std::string const &host, std::string const &port);
    TCP_client(ITCP_server const &server);
    ~TCP_client(void);
    uintmax_t	recv(uint8_t &data, uintmax_t size) const;
    uintmax_t	send(uint8_t const &data, uintmax_t size) const;
private:
    static int	aux_connect(struct addrinfo const *rp);
    static int	connect(std::string const &host, std::string const &port);
    static int	accept(ITCP_server const &server);
};

class	TCP_client_exception : public ITCP_client_exception
{
public:
    TCP_client_exception(char const *what) noexcept;
    TCP_client_exception(std::string const &&what) noexcept;
    char const	*what(void) const noexcept;
private:
    std::string const m_what;
};

#endif		/* !TCP_CLIENT_HPP_ */
