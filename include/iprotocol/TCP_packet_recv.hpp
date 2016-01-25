//
// TCP_packet_recv.hpp for TCP_packet_recv in /home/plasko_a/projet/cplusplus/rtype/include/iprotocol
// 
// Made by Antoine Plaskowski
// Login   <antoine.plaskowski@epitech.eu>
// 
// Started on  Sun Dec  6 04:00:47 2015 Antoine Plaskowski
// Last update Thu Dec 10 03:46:46 2015 Antoine Plaskowski
//

#ifndef		TCP_PACKET_RECV_HPP_
# define	TCP_PACKET_RECV_HPP_

# include	<limits>
# include	<cstring>
# include	"ATCP_packet.hpp"

class	TCP_packet_recv : public ATCP_packet
{
public:
  TCP_packet_recv(void);
  ~TCP_packet_recv(void);
  template<typename T>
  void	get(T &value)
  {
    uint8_t	*data(reinterpret_cast<uint8_t *>(&value));

    for (uintmax_t i = 0; i < sizeof(T); i++)
      data[i] = m_packet.data[m_packet.size++];
  }
  void	get(std::string &string);
  //  void	get(ITCP_protocol::Error &error);
  bool	recv(ITCP_client const &socket);
private:
  uintmax_t	m_recv;
};

#endif		/* !TCP_PACKET_RECV_HPP_ */
