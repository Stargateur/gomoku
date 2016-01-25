//
// TCP_protocol.cpp for TCP_protocol in /home/plasko_a/projet/cplusplus/rtype
// 
// Made by Antoine Plaskowski
// Login   <antoine.plaskowski@epitech.eu>
// 
// Started on  Sun Dec  6 03:40:34 2015 Antoine Plaskowski
// Last update Mon Jan 25 21:05:32 2016 Antoine Plaskowski
//

#include	<algorithm>
#include	<iostream>
#include	"TCP_protocol.hpp"

template<typename T>
TCP_protocol<T>::TCP_protocol(typename ITCP_protocol<T>::Callback *callback, T *data) :
  m_callback(callback),
  m_data(data)
{
}

template<typename T>
TCP_protocol<T>::~TCP_protocol(void)
{
}

template<typename T>
void	TCP_protocol<T>::set_callback(typename ITCP_protocol<T>::Callback *callback)
{
  m_callback = callback;
}

template<typename T>
T	*TCP_protocol<T>::get_data(void)
{
  return (m_data);
}

template<typename T>
T const	*TCP_protocol<T>::get_data(void) const
{
  return (m_data);
}

template<typename T>
void	TCP_protocol<T>::set_data(T *data)
{
  m_data = data;
}

template<typename T>
void	TCP_protocol<T>::set_to_send(TCP_packet_send *to_send, ATCP_packet::Opcode opcode)
{
  to_send->set_opcode(opcode);
#ifdef	DEBUG
  std::cerr << "je prépare un packet " << to_send->get_opcode() << to_send << std::endl;
#endif	/* !DEBUG */
  m_to_send.push_back(to_send);
}

template<typename T>
bool	TCP_protocol<T>::want_send(void) const
{
  return (m_to_send.size() != 0);
}

template<typename T>
bool	TCP_protocol<T>::want_recv(void) const
{
  return (true);
}

template<typename T>
void	TCP_protocol<T>::send(ITCP_client const &socket)
{
  if (m_to_send.size() == 0)
    throw std::logic_error("il n'y a rien a envoyé");
  TCP_packet_send	*to_send = m_to_send.front();
#ifdef	DEBUG
  std::cerr << "j'envoie sur une socket client tcp " << to_send->get_opcode() << to_send << std::endl;
#endif	/* !DEBUG */

  to_send->send(socket);
  m_to_send.pop_front();
  //  delete to_send;
}

template<typename T>
void	TCP_protocol<T>::recv(ITCP_client const &socket)
{  
#ifdef	DEBUG
  std::cerr << "je lis une socket tcp " << std::endl;
#endif	/* !DEBUG */
  if (m_to_recv.recv(socket) == false)
    return;
#ifdef	DEBUG
  std::cerr << "j'ai lu un paquet tcp " << m_to_recv.get_opcode() << std::endl;
#endif	/* !DEBUG */
  switch (m_to_recv.get_opcode())
    {
    case ATCP_packet::Result:
      recv_result();
      return;
    case ATCP_packet::Connect:
      recv_connect();
      return;
    case ATCP_packet::Disconnect:
      recv_disconnect();
      return;
    case ATCP_packet::Ping:
      recv_ping();
      return;
    case ATCP_packet::Pong:
      recv_pong();
      return;
    }
  throw std::exception();
}

template<typename T>
void	TCP_protocol<T>::send_result(typename ITCP_protocol<T>::Error error)
{
  TCP_packet_send	*to_send = new TCP_packet_send();
  to_send->put(error);
  set_to_send(to_send, ATCP_packet::Result);
}

template<typename T>
void	TCP_protocol<T>::recv_result(void)
{
  typename ITCP_protocol<T>::Error	error;
  m_to_recv.get(error);
  m_callback->result(*this, error);
}

template<typename T>
void	TCP_protocol<T>::send_connect(std::string const &login, std::string const &password)
{
  TCP_packet_send	*to_send = new TCP_packet_send();
  to_send->put<uint8_t>(1);
  to_send->put(login);
  to_send->put(password);
  set_to_send(to_send, ATCP_packet::Connect);
}

template<typename T>
void	TCP_protocol<T>::recv_connect(void)
{
  std::string	login;
  std::string	password;
  uint8_t	version;

  m_to_recv.get(version);
  m_to_recv.get(login);
  m_to_recv.get(password);
  if (version != 1) // chiant !
    throw std::exception();
  m_callback->connect(*this, login, password);
}

template<typename T>
void	TCP_protocol<T>::send_disconnect(void)
{
  TCP_packet_send	*to_send = new TCP_packet_send();
  set_to_send(to_send, ATCP_packet::Disconnect);
}

template<typename T>
void	TCP_protocol<T>::recv_disconnect(void)
{
  m_callback->disconnect(*this);
}

template<typename T>
void	TCP_protocol<T>::send_ping(void)
{
  TCP_packet_send	*to_send = new TCP_packet_send();
  set_to_send(to_send, ATCP_packet::Ping);
}

template<typename T>
void	TCP_protocol<T>::recv_ping(void)
{
  m_callback->ping(*this);
}

template<typename T>
void	TCP_protocol<T>::send_pong(void)
{
  TCP_packet_send	*to_send = new TCP_packet_send();
  set_to_send(to_send, ATCP_packet::Pong);
}

template<typename T>
void	TCP_protocol<T>::recv_pong(void)
{
  m_callback->pong(*this);
}
