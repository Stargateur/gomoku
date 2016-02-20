#include    "ITCP_protocol.hpp"
#include    "Client.hpp"
#include    "ITime.hpp"

class Utils
{
public:
    static void    timeout(iprotocol::ITCP_protocol<Client> &itcp_protocol, ITime &timeout);
};