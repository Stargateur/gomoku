#ifndef		ITCP_SERVER_HPP_
# define	ITCP_SERVER_HPP_

# include	"ASocket.hpp"
# include	"ITCP_client.hpp"

class	ITCP_server : virtual public ISocket
{
public:
    virtual ~ITCP_server(void);
    virtual ITCP_client	&accept(void) const = 0;
};

class	ITCP_server_exception : public ISocket_exception
{
public:
    ITCP_server_exception(void) noexcept;
    ITCP_server_exception(ITCP_server_exception const &) noexcept;
    virtual ~ITCP_server_exception(void) noexcept;
    ITCP_server_exception	&operator=(ITCP_server_exception const &) noexcept;
};

#endif		/* !ITCP_SERVER_HPP_ */
