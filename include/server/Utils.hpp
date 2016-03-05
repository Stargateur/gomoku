#include    <chrono>
#include    "ITCP_protocol.hpp"
#include    "Client.hpp"

class Utils
{
public:
    static void    timeout(iprotocol::ITCP_protocol<Client> &itcp_protocol, std::chrono::seconds const &timeout);
};

class   Timeout_exception : public std::exception
{
public:
    Timeout_exception(void) noexcept;
    Timeout_exception(Timeout_exception const &) noexcept;
    virtual ~Timeout_exception(void) noexcept;
    virtual char const  *what(void) const noexcept;
    Timeout_exception   &operator=(Timeout_exception const &) noexcept;
};