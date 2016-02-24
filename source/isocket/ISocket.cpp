#include	"ISocket.hpp"

ISocket::~ISocket(void)
{
}

ISocket_exception::ISocket_exception(void) noexcept
{
}

ISocket_exception::ISocket_exception(ISocket_exception const &) noexcept
{
}

ISocket_exception::~ISocket_exception(void) noexcept
{
}

ISocket_exception     &ISocket_exception::operator=(ISocket_exception const &) noexcept
{
    return (*this);
}

