#include	"ITCP_client.hpp"

ITCP_client::~ITCP_client(void)
{
}

ITCP_client_exception::ITCP_client_exception(void) noexcept
{
}

ITCP_client_exception::ITCP_client_exception(ITCP_client_exception const &) noexcept :
ISocket_exception()
{
}

ITCP_client_exception::~ITCP_client_exception(void) noexcept
{
}

ITCP_client_exception	&ITCP_client_exception::operator=(ITCP_client_exception const &) noexcept
{
    return (*this);
}
