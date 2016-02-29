#ifndef		ITCP_CLIENT_HPP_
# define	ITCP_CLIENT_HPP_

# include	<cstdint>
# include	<string>
# include	"ASocket.hpp"

class	ITCP_client : virtual public ISocket
{
public:
    virtual ~ITCP_client(void);
    virtual uintmax_t	recv(uint8_t &data, uintmax_t size) const = 0;
    virtual uintmax_t	send(uint8_t const &data, uintmax_t size) const = 0;
};

class	ITCP_client_exception : public ISocket_exception
{
public:
    ITCP_client_exception(void) noexcept;
    ITCP_client_exception(ITCP_client_exception const &) noexcept;
    virtual ~ITCP_client_exception(void) noexcept;
    ITCP_client_exception	&operator=(ITCP_client_exception const &) noexcept;
};

#endif		/* !ITCP_TCP_CLIENT_HPP_ */
