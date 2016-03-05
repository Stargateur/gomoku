#include    "TCP_protocol.hpp"

iprotocol::TCP_protocol_exception::TCP_protocol_exception(std::string &&what) noexcept :
    m_what(what)
{
}

iprotocol::TCP_protocol_exception::TCP_protocol_exception(TCP_protocol_exception const &other) noexcept :
    ITCP_protocol_exception(),
    m_what(other.m_what)
{
}

iprotocol::TCP_protocol_exception::~TCP_protocol_exception(void) noexcept
{
}

iprotocol::TCP_protocol_exception     &iprotocol::TCP_protocol_exception::operator=(TCP_protocol_exception const &other) noexcept
{
    m_what = other.m_what;
    return (*this);
}

char const  *iprotocol::TCP_protocol_exception::TCP_protocol_exception::what(void) const noexcept
{
    return (m_what.c_str());
}