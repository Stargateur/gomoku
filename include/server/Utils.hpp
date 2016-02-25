#include    <chrono>
#include    "ITCP_protocol.hpp"
#include    "Client.hpp"

class Utils
{
public:
    static void    timeout(iprotocol::ITCP_protocol<Client> &itcp_protocol, std::chrono::seconds const &timeout);
};