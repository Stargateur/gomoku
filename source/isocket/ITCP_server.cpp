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

