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
            static_assert(std::is_arithmetic<T>::value || std::is_enum<T>::value, "put only arithmetic or enum type");
            uint8_t	*data(reinterpret_cast<uint8_t *>(&value));

            for (uintmax_t i = 0; i < sizeof(T); i++)
                data[i] = m_packet.data[m_packet.size++];
        }
        void	get(std::string &string);
        bool	recv(ITCP_client const &socket);
    private:
        uintmax_t	m_recv;
    };
}

#endif		/* !TCP_PACKET_RECV_HPP_ */
