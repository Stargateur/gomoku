//
// UDP_protocol.hpp for UDP_protocol in /home/plasko_a/projet/cplusplus/rtype/include/iprotocol
// 
// Made by Antoine Plaskowski
// Login   <antoine.plaskowski@epitech.eu>
// 
// Started on  Sun Dec  6 03:35:29 2015 Antoine Plaskowski
// Last update Sat Dec 26 15:45:32 2015 Antoine Plaskowski
//

#ifndef		UDP_PROTOCOL_HPP_
# define	UDP_PROTOCOL_HPP_

# include	<cstdint>
# include	<string>
# include	<array>
# include	<tuple>
# include	"IUDP_protocol.hpp"
# include	"ISelect.hpp"

class	UDP_protocol : public IUDP_protocol
{
public:
  UDP_protocol(IUDP_protocol::Callback &callback);
  ~UDP_protocol(void);
private:
  //  void	set_callback(IUDP_protocol::Callback &callback);
public:
  bool	want_send(void) const;
  bool	want_recv(void) const;
  bool	want_sendto(void) const;
  bool	want_recvfrom(void) const;
  void	send(IUDP_client const &socket);
  void	recv(IUDP_client const &socket);
  void	sendto(IUDP_server const &socket);
  void	recvfrom(IUDP_server const &socket);
  void	send_sprites(std::list<IUDP_protocol::Sprite *> const &sprites);
  void	send_sounds(std::list<IUDP_protocol::Sound *> const &sounds);
  void	send_input(std::string const &login, IUDP_protocol::Input const &inputs);
  void	send_sprites(std::list<IUDP_protocol::Sprite *> const &sprites, IUDP_server::u_sockaddr const &sockaddr, socklen_t len);
  void	send_sounds(std::list<IUDP_protocol::Sound *> const &sounds, IUDP_server::u_sockaddr const &sockaddr, socklen_t len);
  void	send_input(std::string const &login, IUDP_protocol::Input const &inputs, IUDP_server::u_sockaddr const &sockaddr, socklen_t len);
private:
  void	recv_sprites(void);
  void	recv_sounds(void);
  void	recv_input(void);
  void	recv_sprites(IUDP_server::u_sockaddr const &sockaddr, socklen_t len);
  void	recv_sounds(IUDP_server::u_sockaddr const &sockaddr, socklen_t len);
  void	recv_input(IUDP_server::u_sockaddr const &sockaddr, socklen_t len);
private:
  IUDP_protocol::Callback	&m_callback;
  UDP_packet_recv	m_to_recv;
  std::list<UDP_packet_send *>	m_to_send;
  using m_sendto = std::tuple<UDP_packet_send, IUDP_server::u_sockaddr, socklen_t>;
  std::list<m_sendto *>	m_to_sendto;
private:
  //  UDP_packet_send	&get_to_send(void);
  void	set_to_send(UDP_packet_send *to_send, AUDP_packet::Opcode opcode);
  void	set_to_send(m_sendto *to_send, AUDP_packet::Opcode opcode, IUDP_server::u_sockaddr const &sockaddr, socklen_t len);
};

#endif		/* !UDP_PROTOCOL_HPP_ */
