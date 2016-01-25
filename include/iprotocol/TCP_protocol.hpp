//
// TCP_protocol.hpp for TCP_protocol in /home/plasko_a/projet/cplusplus/rtype/include/iprotocol
// 
// Made by Antoine Plaskowski
// Login   <antoine.plaskowski@epitech.eu>
// 
// Started on  Sun Dec  6 03:35:29 2015 Antoine Plaskowski
// Last update Mon Jan 25 21:09:44 2016 Antoine Plaskowski
//

#ifndef		TCP_PROTOCOL_HPP_
# define	TCP_PROTOCOL_HPP_

# include	<cstdint>
# include	<string>
# include	<array>
# include	"ITCP_protocol.hpp"
# include	"ISelect.hpp"

template<typename T>
class	TCP_protocol : public ITCP_protocol<T>
{
public:
  TCP_protocol(typename ITCP_protocol<T>::Callback *callback, T *data);
  ~TCP_protocol(void);
  void	set_callback(typename ITCP_protocol<T>::Callback *callback);
  T	*get_data(void);
  T const	*get_data(void) const;
  void	set_data(T *data);
private:
  void	set_to_send(TCP_packet_send *to_send, ATCP_packet::Opcode opcode);
public:
  bool	want_send(void) const;
  bool	want_recv(void) const;
  void	send(ITCP_client const &socket);
  void	recv(ITCP_client const &socket);
  void	send_result(typename ITCP_protocol<T>::Error error);
  void	send_connect(std::string const &login, std::string const &password);
  void	send_disconnect(void);
  void	send_ping(void);
  void	send_pong(void);
  template<typename... Ts>
  void	test(TCP_packet_send *to_send, ATCP_packet::Opcode opcode, Ts... args)
  {
    if (sizeof...(args) > 0)
      test(to_send, opcode, args...);
    else
      set_to_send(to_send, opcode);
  }
  template<typename Toto, typename... Ts>
  void	test(TCP_packet_send *to_send, ATCP_packet::Opcode opcode, Toto first, Ts... args)
  {
    to_send->put(first);
    test(to_send, opcode, args...);
  }
private:
  void	recv_result(void);
  void	recv_connect(void);
  void	recv_disconnect(void);
  void	recv_ping(void);
  void	recv_pong(void);
private:
  typename ITCP_protocol<T>::Callback	*m_callback;
  T	*m_data;
  TCP_packet_recv	m_to_recv;
  std::list<TCP_packet_send *>	m_to_send;
};

#include	"../../source/iprotocol/TCP_protocol.cpp"

#endif		/* !TCP_PROTOCOL_HPP_ */
