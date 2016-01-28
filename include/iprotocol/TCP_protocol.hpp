//
// TCP_protocol.hpp for TCP_protocol in /home/plasko_a/projet/cplusplus/rtype/include/iprotocol
// 
// Made by Antoine Plaskowski
// Login   <antoine.plaskowski@epitech.eu>
// 
// Started on  Sun Dec  6 03:35:29 2015 Antoine Plaskowski
// Last update Tue Jan 26 17:55:39 2016 Antoine Plaskowski
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
  uint8_t	get_version(void) const
  {
    return (1);
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
	std::cerr << "Finis d'écrire" << std::endl;
#endif	/* !DEBUG */    
	delete to_send;
      }
    else
      {
#ifdef	DEBUG
	std::cerr << "Reste à écrire" << std::endl;
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
    to_send.put<uint8_t>(get_version());
    to_send.put(login);
    to_send.put(password);
  }

private:
  void	recv_connect(void)
  {
    std::string	*login = new std::string();
    std::string	*password = new std::string();
    uint8_t	version;

    m_to_recv.get(version);
    m_to_recv.get(*login);
    m_to_recv.get(*password);
    m_callback->connect(*this, version, login, password);
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
    typename ITCP_protocol<T>::Game	*game = new typename ITCP_protocol<T>::Game();
    game->name = new std::string();
    game->owner = new std::string();
    get_rec(m_to_recv, *game->name, *game->owner);
    m_callback->create_game(*this, game);
  }

public:
  void	send_join_game(typename ITCP_protocol<T>::Game const &game)
  {
    set_rec(get_to_send(ATCP_packet::Join_game), *game.name, *game.owner);
  }

private:
  void	recv_join_game(void)
  {
    typename ITCP_protocol<T>::Game	*game = new typename ITCP_protocol<T>::Game();
    game->name = new std::string();
    game->owner = new std::string();
    get_rec(m_to_recv, *game->name, *game->owner);
    m_callback->join_game(*this, game);
  }

public:
  void	send_leave_game(void)
  {
    set_rec(get_to_send(ATCP_packet::Leave_game));
  }

private:
  void	recv_leave_game(void)
  {
    m_callback->leave_game(*this);
  }

public:
  void	send_put_stone_game(typename ITCP_protocol<T>::Game_stone const &stone)
  {
    set_rec(get_to_send(ATCP_packet::Put_stone_game), stone.x, stone.y, stone.color);
  }

private:
  void	recv_put_stone_game(void)
  {
    typename ITCP_protocol<T>::Game_stone *stone = new typename ITCP_protocol<T>::Game_stone();
    get_rec(m_to_recv, stone->x, stone->y, stone->color);
    m_callback->put_stone_game(*this, stone);
  }

public:
  void	send_change_param_game(typename ITCP_protocol<T>::Game_param const &param)
  {
    set_rec(get_to_send(ATCP_packet::Change_param_game), *param.name, *param.value);
  }

private:
  void	recv_change_param_game(void)
  {
    typename ITCP_protocol<T>::Game_param *param = new typename ITCP_protocol<T>::Game_param();
    param->name = new std::string();
    param->value = new std::string();
    get_rec(m_to_recv, *param->name, *param->owner);
    m_callback->change_param_game(*this, param);
  }

public:
  void	send_list_param_game(std::list<typename ITCP_protocol<T>::Game_param *> const &params)
  {
    TCP_packet_send &to_send = get_to_send(ATCP_packet::List_param_game);
    to_send.put(static_cast<uint8_t>(params.size()));
    for (auto param : params)
      set_rec(to_send, *param->name, *param->value);
  }

private:
  void	recv_list_param_game(void)
  {
    std::list<typename ITCP_protocol<T>::Game_param *> *params = new std::list<typename ITCP_protocol<T>::Game_param *>();
    uint8_t	size;
    m_to_recv.get(size);
  }

public:
  void	send_game_created(typename ITCP_protocol<T>::Game const &game)
  {
    TCP_packet_send &to_send = get_to_send(ATCP_packet::Game_created);
    set_rec(to_send, *game.name, *game.owner);
  }

private:
  void	recv_game_created(void)
  {
    typename ITCP_protocol<T>::Game *game = new typename ITCP_protocol<T>::Game();
    game->name = new std::string();
    game->value = new std::string();
    get_rec(m_to_recv, *game->name, *game->value);
    m_callback->game_created(*this, game);
  }

public:
  void	send_game_player_joined(std::string const &name)
  {
    TCP_packet_send &to_send = get_to_send(ATCP_packet::Game_player_joined);
    set_rec(to_send, name);
  }

private:
  void	recv_game_player_joined(void)
  {
    std::string *name = new std::string();
    get_rec(m_to_recv, name);
    m_callback->game_player_joined(*this, name);
  }

public:
  void	send_game_player_left(std::string const &name)
  {
    TCP_packet_send &to_send = get_to_send(ATCP_packet::Game_player_left);
    set_rec(to_send, name);
  }

private:
  void	recv_game_player_left(void)
  {
    std::string *name = new std::string();
    get_rec(m_to_recv, name);
    m_callback->game_player_left(*this, name);
  }

public:
  void	send_game_param_changed(typename ITCP_protocol<T>::Game_param const &param)
  {
    TCP_packet_send &to_send = get_to_send(ATCP_packet::Game_param_changed);
    set_rec(to_send, *param.name, *param.value);
  }

private:
  void	recv_game_param_changed(void)
  {
    typename ITCP_protocol<T>::Game_param *param = new typename ITCP_protocol<T>::Game_param;
    param->name = new std::string();
    param->value = new std::string();
    get_rec(m_to_recv, *param->name, *param->value);
    m_callback->game_param_changed(*this, param);
  }

public:
  void	send_game_stone_put(typename ITCP_protocol<T>::Game_stone const &stone)
  {
    TCP_packet_send &to_send = get_to_send(ATCP_packet::Game_stone_put);
    set_rec(to_send, stone.x, stone.y, stone.color);
  }

private:
  void	recv_game_stone_put(void)
  {
    typename ITCP_protocol<T>::Game_stone *stone = new typename ITCP_protocol<T>::Game_stone();
    get_rec(m_to_recv, stone->x, stone->y, stone->color);
    m_callback->game_stone_put(*this, stone);
  }

public:
  void	send_game_deleted(typename ITCP_protocol<T>::Game const &game)
  {
    TCP_packet_send &to_send = get_to_send(ATCP_packet::Game_deleted);
    set_rec(to_send, game.name, game.owner);
  }

private:
  void	recv_game_deleted(void)
  {
    typename ITCP_protocol<T>::Game *game = new typename ITCP_protocol<T>::Game_game();
    game->name = new std::string();
    game->owner = new std::string();
    get_rec(m_to_recv, game->name, game->owner);
    m_callback->game_deleted(*this, game);
  }

public:
  void	send_start_game(void)
  {
    TCP_packet_send &to_send = get_to_send(ATCP_packet::Start_game);
    set_rec(to_send);
  }

private:
  void	recv_start_game(void)
  {
    get_rec(m_to_recv);
    m_callback->start_game(*this);
  }

public:
  void	send_ready_game(bool ready)
  {
    TCP_packet_send &to_send = get_to_send(ATCP_packet::Ready_game);
    set_rec(to_send, ready);
  }

private:
  void	recv_ready_game(void)
  {
    bool	ready;
    get_rec(m_to_recv, ready);
    m_callback->ready_game(*this, ready);
  }

public:
  void	send_result_game(typename ITCP_protocol<T>::Game_result const &result)
  {
    TCP_packet_send &to_send = get_to_send(ATCP_packet::Result_game);
    set_rec(to_send, result.winner);
  }

private:
  void	recv_result_game(void)
  {
    typename ITCP_protocol<T>::Game_result *result = new typename ITCP_protocol<T>::Game_result();
    result->winner = new std::string();
    get_rec(m_to_recv, result->winner);
    m_callback->result_game(*this, result);
  }

public:
  void	send_message(typename ITCP_protocol<T>::Message const &message)
  {
    TCP_packet_send &to_send = get_to_send(ATCP_packet::Message);
    set_rec(to_send, *message.name, *message.message);
  }

private:
  void	recv_message(void)
  {
    typename ITCP_protocol<T>::Message *message = new typename ITCP_protocol<T>::Message();
    message->name = new std::string();
    message->owner = new std::string();
    get_rec(m_to_recv, *message->name, *message->owner);
    m_callback->message(*this, message);
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