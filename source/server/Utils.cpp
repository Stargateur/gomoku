#include    <iostream>
#include    "Utils.hpp"

void    Utils::timeout(iprotocol::ITCP_protocol<Client> &itcp_protocol, std::chrono::seconds const &timeout)
{
    Client  &client = *itcp_protocol.get_data();
    std::chrono::steady_clock::time_point   &last = client.get_last();
    std::chrono::steady_clock::time_point   now = std::chrono::steady_clock::now();
    std::chrono::seconds seconds = std::chrono::duration_cast<std::chrono::seconds>(now - last);

    #ifndef NDEBUG
    std::cerr << "Test du timeout avec " << timeout.count() << " et " << seconds.count() << "s" << std::endl;
    #endif
    if (seconds > timeout)
    {
        if (client.get_wait_pong() == true)
        {
            #ifndef NDEBUG
            std::cerr << "le client a timeout deuxième fois" << std::endl;
            #endif
            throw std::logic_error("timeout");
        }
        #ifndef NDEBUG
        std::cerr << "le client a timeout première fois" << std::endl;
        #endif
        last = now;
        client.set_wait_pong(true);
        itcp_protocol.send_ping();
        return;
    }
    #ifndef NDEBUG
    std::cerr << "le client n'as pas timeout" << std::endl;
    #endif
}
