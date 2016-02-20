#include    "ITCP_protocol.hpp"

iprotocol::ITCP_protocol_exception::~ITCP_protocol_exception(void) noexcept
{
}

iprotocol::ITCP_protocol_exception::ITCP_protocol_exception(void) noexcept
{
}

iprotocol::ITCP_protocol_exception::ITCP_protocol_exception(ITCP_protocol_exception const &) noexcept
{
}

iprotocol::ITCP_protocol_exception   &iprotocol::ITCP_protocol_exception::operator=(ITCP_protocol_exception const &) noexcept
{
    return (*this);
}

char const  *iprotocol::ITCP_protocol_exception::what(void) const noexcept
{
    return ("ITCP_protocol_exception");
}