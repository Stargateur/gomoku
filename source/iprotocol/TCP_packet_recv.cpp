#include	<iostream>
#include    <stdexcept>
#include	"TCP_packet_recv.hpp"

iprotocol::TCP_packet_recv::TCP_packet_recv(void) :
    iprotocol::ATCP_packet(),
    m_recv(0)
{
}

iprotocol::TCP_packet_recv::~TCP_packet_recv(void)
{
}

bool	iprotocol::TCP_packet_recv::recv(ITCP_client const &socket)
{
    if (m_recv >= sizeof(m_buffer))
        throw iprotocol::ATCP_packet_exception();
    uintmax_t	ret;
    if (m_recv < m_size_header)
	{
        ret = socket.recv(m_buffer[m_recv], m_size_header - m_recv);
		    if (ret > m_size_header - m_recv)
        throw iprotocol::ATCP_packet_exception();
	}
    else
	{
        ret = socket.recv(m_buffer[m_recv], m_size_header + get_size() - m_recv);
    if (ret > m_size_header + get_size() - m_recv)
        throw iprotocol::ATCP_packet_exception();
	}
	#ifndef NDEBUG
    std::cerr << "Nombre d'octect lu " << ret << std::endl;
	#endif
    if (ret == 0)
        throw iprotocol::ATCP_packet_exception();
    m_recv += ret;
    if (m_recv < m_size_header)
        return (false);
    if (m_recv < m_size_header + get_size())
        return (false);
    set_size(0);
    m_recv = 0;
    return (true);
}

void	iprotocol::TCP_packet_recv::get(std::string &string)
{
    uint8_t       size;

    get(size);
    for (uintmax_t i = 0; i < size; i++)
    {
        uint8_t   c;
        get(c);
        string.push_back(static_cast<char>(c));
    }
}
