#include    <iostream>
#include    "Utils.hpp"

void    Utils::timeout(iprotocol::ITCP_protocol<Client> &itcp_protocol, std::chrono::seconds const &timeout)
{
    Client  &client = *itcp_protocol.get_data();
    std::chrono::steady_clock::time_point   &last = client.get_last();
    std::chrono::steady_clock::time_point   now = std::chrono::steady_clock::now();
    std::chrono::seconds seconds = std::chrono::duration_cast<std::chrono::seconds>(now - last);

    #ifndef NDEBUG
    std::cerr << "TIMEOUT : WITH " << timeout.count() << "s and " << seconds.count() << "s" << std::endl;
    #endif
    if (seconds > timeout)
    {
        if (client.get_wait_pong() == true)
        {
            #ifndef NDEBUG
            std::cerr << "TIMEOUT : YES (second time)" << std::endl;
            #endif
            throw Timeout_exception();
        }
        #ifndef NDEBUG
        std::cerr << "TIMEOUT : YES (first time)" << std::endl;
        #endif
        last = now;
        client.set_wait_pong(true);
        itcp_protocol.send_ping();
        return;
    }
    #ifndef NDEBUG
    std::cerr << "TIMEOUT : NO" << std::endl;
    #endif
}

Timeout_exception::Timeout_exception(void) noexcept
{
}

Timeout_exception::Timeout_exception(Timeout_exception const &) noexcept
{
}

Timeout_exception::~Timeout_exception(void) noexcept
{
}

Timeout_exception     &Timeout_exception::operator=(Timeout_exception const &) noexcept
{
    return (*this);
}

char const  *Timeout_exception::Timeout_exception::what(void) const noexcept
{
    return ("Timeout_exception");
}