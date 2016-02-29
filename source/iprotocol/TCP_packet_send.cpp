#include	<iostream>
#include    <stdexcept>
#include	"TCP_packet_send.hpp"

iprotocol::TCP_packet_send::TCP_packet_send(void) :
    iprotocol::ATCP_packet(),
    m_send(0)
{
}

iprotocol::TCP_packet_send::~TCP_packet_send(void)
{
}

bool	iprotocol::TCP_packet_send::send(ITCP_client const &socket)
{
    if (m_send >= sizeof(m_buffer))
        throw iprotocol::ATCP_packet_exception();
    uintmax_t	ret = socket.send(m_buffer[m_send], m_size_header + get_size() - m_send);

	#ifndef NDEBUG
    std::cerr << "TCP_packet_send : Nombre d'octect envoyé " << ret << std::endl;
	#endif
    if (ret > m_size_header + get_size() - m_send)
        throw iprotocol::ATCP_packet_exception();
    if (ret == 0)
        throw iprotocol::ATCP_packet_exception();
    m_send += ret;
    if (m_send < m_size_header + get_size())
        return (false);
    m_send = 0;
    set_size(0);
    return (true);
}

void	iprotocol::TCP_packet_send::put(std::string const &string)
{
    put(static_cast<uint8_t>(string.size()));
    for (uintmax_t i = 0; i < string.size() && i < UINT8_MAX; i++)
        put(static_cast<uint8_t>(string[i]));
}

void	iprotocol::TCP_packet_send::set_opcode(Opcode opcode)
{
    m_packet.opcode = opcode;
}
