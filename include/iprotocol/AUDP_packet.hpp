//
// AUDP_packet.hpp for AUDP_packet in /home/plasko_a/projet/cplusplus/rtype/include/iprotocol
// 
// Made by Antoine Plaskowski
// Login   <antoine.plaskowski@epitech.eu>
// 
// Started on  Sun Dec  6 03:57:06 2015 Antoine Plaskowski
// Last update Tue Dec 22 22:13:47 2015 Antoine Plaskowski
//

#ifndef		AUDP_PACKET_HPP_
# define	AUDP_PACKET_HPP_

# include	<cstdint>
# include	"IUDP_client.hpp"

class	AUDP_packet
{
public:
  enum  Opcode : uint8_t
  {
    Sprites = 0,
    Sounds,
    Input
  };
  AUDP_packet(void);
  virtual ~AUDP_packet(void);
  Opcode	get_opcode(void) const;
  uint8_t	operator[](uint16_t idx) const;
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
  static const	uintmax_t	m_size_header = sizeof(s_packet) - sizeof(uint8_t) * (UINT16_MAX + 1);
};


#endif		/* !AUDP_PACKET_HPP_ */
