//
// TCP_protocol.hpp for TCP_protocol in /home/plasko_a/projet/cplusplus/rtype/include/iprotocol
// 
// Made by Antoine Plaskowski
// Login   <antoine.plaskowski@epitech.eu>
// 
// Started on  Sun Dec  6 03:35:29 2015 Antoine Plaskowski
// Last update Tue Jan 26 13:09:02 2016 Antoine Plaskowski
//

#ifndef		TCP_PROTOCOL_HPP_
# define	TCP_PROTOCOL_HPP_

# include	<algorithm>
# include	<iostream>
# include	<cstdint>
# include	<string>
# include	<array>
# include	"ITCP_protocol.hpp"
# include	"ISelect.hpp"

template<typename T>
class	TCP_protocol : public ITCP_protocol<T>
{
public:
  TCP_protocol(typename ITCP_protocol<T>::Callback *callback, T *data = nullptr) :
    m_callback(callback),
    m_data(data)
  {
    if (callback == nullptr)
      throw std::logic_error("callback can't be nullptr");
  }

public:
  ~TCP_protocol(void)
  {
  }

public:
  void	set_callback(typename ITCP_protocol<T>::Callback *callback)
  {
    if (callback == nullptr)
      throw std::logic_error("callback can't be nullptr");
    m_callback = callback;
  }

public:
  T	*get_data(void)
  {
    return (m_data);
  }

public:
  T const	*get_data(void) const
  {
    return (m_data);
  }

public:
  void	set_data(T *data)
  {
    m_data = data;
  }

private:
  TCP_packet_send	&get_to_send(ATCP_packet::Opcode opcode)
  {
    TCP_packet_send	*to_send = new TCP_packet_send();
    to_send->set_opcode(opcode);
#ifdef	DEBUG
    std::cerr << "je prépare un packet " << to_send->get_opcode() << " " << to_send << std::endl;
#endif	/* !DEBUG */
    m_to_send.push_back(to_send);
    return (*to_send);
  }

public:
  bool	want_send(void) const
  {
    return (m_to_send.size() != 0);
  }

public:
  bool	want_recv(void) const
  {
    return (true);
  }

public:
  void	send(ITCP_client const &socket)
  {
    if (m_to_send.size() == 0)
      throw std::logic_error("il n'y a rien a envoyé");
    TCP_packet_send	*to_send = m_to_send.front();
#ifdef	DEBUG
    std::cerr << "j'envoie sur une socket client tcp " << to_send->get_opcode() << " " << to_send << std::endl;
#endif	/* !DEBUG */    
    m_to_send.pop_front();
    if (to_send->send(socket))
      {
#ifdef	DEBUG
	std::cerr << "Success en une fois" << std::endl;
#endif	/* !DEBUG */    
	delete to_send;
      }
    else
      {
#ifdef	DEBUG
	std::cerr << "Fail en une fois" << std::endl;
#endif	/* !DEBUG */    
      }
  }

public:
  void	recv(ITCP_client const &socket)
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
      case ATCP_packet::Create_game:
	recv_create_game();
	return;
      case ATCP_packet::Join_game:
	return;
      case ATCP_packet::Leave_game:
	return;
      case ATCP_packet::Put_stone_game:
	return;
      case ATCP_packet::Change_param_game:
	return;
      case ATCP_packet::List_param_game:
	return;
      case ATCP_packet::Game_created:
	return;
      case ATCP_packet::Game_player_joined:
	return;
      case ATCP_packet::Game_player_left:
	return;
      case ATCP_packet::Game_param_changed:
	return;
      case ATCP_packet::Game_stone_put:
	return;
      case ATCP_packet::Game_deleted:
	return;
      case ATCP_packet::Start_game:
	return;
      case ATCP_packet::Ready_game:
	return;
      case ATCP_packet::Result_game:
	return;
      case ATCP_packet::Message:
	return;
      }
    throw std::logic_error("recv a Unknow opcode");
  }

public:
  void	send_result(typename ITCP_protocol<T>::Error error)
  {
    TCP_packet_send	&to_send = get_to_send(ATCP_packet::Result);;
    to_send.put(error);    
  }

private:
  void	recv_result(void)
  {
    typename ITCP_protocol<T>::Error	error;
    m_to_recv.get(error);
    m_callback->result(*this, error);
  }

public:
  void	send_connect(std::string const &login, std::string const &password)
  {
    TCP_packet_send	&to_send = get_to_send(ATCP_packet::Connect);
    to_send.put<uint8_t>(1);
    to_send.put(login);
    to_send.put(password);
  }

private:
  void	recv_connect(void)
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

public:
  void	send_disconnect(void)
  {
    get_to_send(ATCP_packet::Disconnect);
  }

private:
  void	recv_disconnect(void)
  {
    m_callback->disconnect(*this);
  }

public:
  void	send_ping(void)
  {
    get_to_send(ATCP_packet::Ping);
  }

private:
  void	recv_ping(void)
  {
    m_callback->ping(*this);
  }

public:
  void	send_pong(void)
  {
    get_to_send(ATCP_packet::Pong);
  }

private:
  void	recv_pong(void)
  {
    m_callback->pong(*this);
  }

public:
  void	send_create_game(typename ITCP_protocol<T>::Game const &game)
  {
    set_rec(get_to_send(ATCP_packet::Create_game), *game.name, *game.owner);
  }

private:
  void	recv_create_game(void)
  {
    typename ITCP_protocol<T>::Game	game;
    game.name = new std::string();
    game.owner = new std::string();
    get_rec(m_to_recv, *game.name, *game.owner);
    m_callback->create_game(*this, game);
  }

private:
  template<typename... Ts>
  static void	set_rec(TCP_packet_send &)
  {
  }

private:
  template<typename Arg, typename... Args>
  static void	set_rec(TCP_packet_send &to_send, Arg &first, Args &... args)
  {
    to_send.put(first);
    set_rec(to_send, args...);
  }

private:
  template<typename... Args>
  static void	get_rec(TCP_packet_recv &)
  {
  }

private:
  template<typename Arg, typename... Args>
  static void	get_rec(TCP_packet_recv &to_recv, Arg &first, Args &... args)
  {
    to_recv.get(first);
    get_rec(to_recv, args...);
  }

private:
  typename ITCP_protocol<T>::Callback	*m_callback;
  T	*m_data;
  TCP_packet_recv	m_to_recv;
  std::list<TCP_packet_send *>	m_to_send;
};

#endif		/* !TCP_PROTOCOL_HPP_ */
