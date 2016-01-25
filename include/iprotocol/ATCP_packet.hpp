//
// ATCP_packet.hpp for ATCP_packet in /home/plasko_a/projet/cplusplus/rtype/include/iprotocol
// 
// Made by Antoine Plaskowski
// Login   <antoine.plaskowski@epitech.eu>
// 
// Started on  Sun Dec  6 03:57:06 2015 Antoine Plaskowski
// Last update Sun Dec 27 18:02:15 2015 Antoine Plaskowski
//

#ifndef		ATCP_PACKET_HPP_
# define	ATCP_PACKET_HPP_

# include	<cstdint>
# include	<ostream>
# include	"ITCP_client.hpp"

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
    List_meta_games,
    Meta_games,
    Create_game,
    Join_game,
    Message,
    List_meta_params,
    Meta_params,
    Change_param,
    List_meta_sprites,
    Meta_sprites,
    Take_sprite,
    Give_sprite,
    List_meta_sounds,
    Meta_sounds,
    Take_sound,
    Give_sound,
    Ready,
    Start,
    End,
    Leave
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

std::ostream    &operator<<(std::ostream &os, ATCP_packet::Opcode opcode);

#endif		/* !ATCP_PACKET_HPP_ */
