#include    "ITCP_protocol.hpp"
#include    "Client.hpp"
#include    "ITime.hpp"

class Utils
{
public:
    static void    timeout(ITCP_protocol<Client> &itcp_protocol, ITime &timeout);
};