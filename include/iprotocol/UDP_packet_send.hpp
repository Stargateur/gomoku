//
// UDP_packet_send.hpp for UDP_packet_send in /home/plasko_a/projet/cplusplus/rtype/include/iprotocol
// 
// Made by Antoine Plaskowski
// Login   <antoine.plaskowski@epitech.eu>
// 
// Started on  Sun Dec  6 04:02:59 2015 Antoine Plaskowski
// Last update Tue Dec 22 21:07:00 2015 Antoine Plaskowski
//

#ifndef		UDP_PACKET_SEND_HPP_
# define	UDP_PACKET_SEND_HPP_

# include	<limits>
# include	"AUDP_packet.hpp"

class	UDP_packet_send : public AUDP_packet
{
public:
  UDP_packet_send(void);
  ~UDP_packet_send(void);
  template<typename T>
  void	put(T const &value)
  {
    uint8_t const	*data(reinterpret_cast<uint8_t const *>(&value));
    for (uintmax_t i = 0; i < sizeof(T); i++)
      m_packet.data[m_packet.size++] = data[i];
  }
  void	put(std::string const &string);
  void	send(IUDP_client const &socket);
  void	sendto(IUDP_server const &socket, IUDP_server::u_sockaddr &sockaddr, socklen_t &len);
  void	set_opcode(Opcode opcode);
};

#endif		/* !UDP_PACKET_SEND_HPP_ */
