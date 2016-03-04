#ifndef		ATCP_PACKET_HPP_
# define	ATCP_PACKET_HPP_

# include	<cstdint>
# include	<ostream>
# include	"ITCP_client.hpp"

namespace iprotocol
{
    class	ATCP_packet
    {
    public:
        enum  Opcode : uint8_t
        {
            Result = 0,
            Connect,
            Disconnect,
            Ping,
            Pong,
            Game_create,
            Game_delete,
            Game_join,
            Game_leave,
            Game_stone_put,
            Game_param,
            Game_player_param,
            Game_player_join,
            Game_player_leave,
            Game_start,
            Game_ready,
            Game_score,
            Game_help,
            Game_hint,
            Game_result,
            Game_message,
        };
        ATCP_packet(void);
        virtual ~ATCP_packet(void);
        Opcode	get_opcode(void) const;
        uint8_t	operator[](uint16_t idx) const;
        static char const	*get_str_opcode(Opcode opcode);
    protected:
        void	set_size(uint16_t size);
        uintmax_t	get_size(void) const;
    protected:
    #pragma	pack(1)
        struct	s_packet
        {
            Opcode	opcode;
            uint16_t	size;
            uint8_t	data[UINT16_MAX + 1];
        };
        union
        {
            s_packet	m_packet;
            uint8_t	m_buffer[sizeof(s_packet)];
        };
    #pragma	pack()
    public:
        static const	uintmax_t	m_size_header = sizeof(s_packet) - (sizeof(uint8_t) * (UINT16_MAX + 1));
    };

    class ATCP_packet_exception : public std::exception
    {
    public:
        ATCP_packet_exception(void) noexcept;
        ATCP_packet_exception(ATCP_packet_exception const &) noexcept; 
        ~ATCP_packet_exception(void) noexcept;
        ATCP_packet_exception   &operator=(ATCP_packet_exception const &) noexcept;
        char const  *what(void) const noexcept;
    };
    std::ostream    &operator<<(std::ostream &os, ATCP_packet::Opcode opcode);
}

#endif		/* !ATCP_PACKET_HPP_ */
