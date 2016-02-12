#include    <iostream>
#include    "Utils.hpp"

void    Utils::timeout(ITCP_protocol<Client> &itcp_protocol, ITime &timeout)
{
    Client  &client = *itcp_protocol.get_data();
    ITime       &last = *client.get_last();
    intmax_t      second = last.get_second();
    intmax_t      nano = last.get_nano();

    last.now();
    #ifndef NDEBUG
    std::cerr << "Test du timeout " << second << "s " << nano << "ns par rapport à ";
    std::cerr << last.get_second() << "s " << last.get_nano() << "n" << std::endl;
    #endif
    if (last.get_second() - second > timeout.get_second()
        || (last.get_second() - second == timeout.get_second()
            && last.get_nano() - nano > timeout.get_nano()))
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
        client.set_wait_pong(true);
        itcp_protocol.send_ping();
        return;
    }
    #ifndef NDEBUG
    std::cerr << "le client n'as pas timeout" << std::endl;
    #endif
    last.set_second(second);
    last.set_nano(nano);
}
