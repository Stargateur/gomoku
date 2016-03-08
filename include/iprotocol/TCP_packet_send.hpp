#ifndef		TCP_PACKET_SEND_HPP_
# define	TCP_PACKET_SEND_HPP_

# include	<limits>
# include	"ATCP_packet.hpp"

namespace iprotocol
{
    class	TCP_packet_send : public ATCP_packet
    {
    public:
        TCP_packet_send(void);
        ~TCP_packet_send(void);
        template<typename T>
        void	put(T const &value)
        {
            static_assert(std::is_arithmetic<T>::value || std::is_enum<T>::value, "put only arithmetic or enum type");
            uint8_t const	*data(reinterpret_cast<uint8_t const *>(&value));
            for (uintmax_t i = 0; i < sizeof(T); i++)
                m_packet.data[m_packet.size++] = data[i];
        }
        void	put(std::string const &string);
        bool	send(ITCP_client const &socket);
        void	set_opcode(Opcode opcode);
    private:
        uintmax_t	m_send;
    };
}

#endif		/* !TCP_PACKET_SEND_HPP_ */
