#ifndef		TCP_PACKET_RECV_HPP_
# define	TCP_PACKET_RECV_HPP_

# include	<limits>
# include	<cstring>
# include	"ATCP_packet.hpp"

namespace iprotocol
{
    class	TCP_packet_recv : public ATCP_packet
    {
    public:
        TCP_packet_recv(void);
        ~TCP_packet_recv(void);
        template<typename T>
        void	get(T &value)
        {
            static_assert(!std::is_pointer<T>::value, "send pointer is not allowed");
            uint8_t	*data(reinterpret_cast<uint8_t *>(&value));

            for (uintmax_t i = 0; i < sizeof(T); i++)
                data[i] = m_packet.data[m_packet.size++];
        }
        void	get(std::string &string);
        //  void	get(iprotocol::ITCP_protocol::Error &error);
        bool	recv(ITCP_client const &socket);
    private:
        uintmax_t	m_recv;
    };
}

#endif		/* !TCP_PACKET_RECV_HPP_ */
