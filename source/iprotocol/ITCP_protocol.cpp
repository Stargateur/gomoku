#include    "ITCP_protocol.hpp"

ITCP_protocol_exception::~ITCP_protocol_exception(void) noexcept
{
}

ITCP_protocol_exception::ITCP_protocol_exception(void) noexcept
{
}

ITCP_protocol_exception::ITCP_protocol_exception(ITCP_protocol_exception const &) noexcept
{
}

ITCP_protocol_exception   &ITCP_protocol_exception::operator=(ITCP_protocol_exception const &) noexcept
{
    return (*this);
}

char const  *ITCP_protocol_exception::what(void) const noexcept
{
    return ("ITCP_protocol_exception");
}