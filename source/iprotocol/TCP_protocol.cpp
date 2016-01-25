//
// TCP_protocol.cpp for TCP_protocol in /home/plasko_a/projet/cplusplus/rtype
// 
// Made by Antoine Plaskowski
// Login   <antoine.plaskowski@epitech.eu>
// 
// Started on  Sun Dec  6 03:40:34 2015 Antoine Plaskowski
// Last update Sun Dec 27 20:53:06 2015 Alaric Degand
//

#include	<algorithm>
#include	<iostream>
#include	"TCP_protocol.hpp"

TCP_protocol::TCP_protocol(ITCP_protocol::Callback &callback) :
  m_callback(callback)
{
}

TCP_protocol::~TCP_protocol(void)
{
}

// void	TCP_protocol::set_callback(ITCP_protocol::Callback &callback)
// {
//   m_callback = &callback;
// }

void	TCP_protocol::set_to_send(TCP_packet_send *to_send, ATCP_packet::Opcode opcode)
{
  to_send->set_opcode(opcode);
#ifdef	DEBUG
  std::cerr << "je prépare un packet " << to_send->get_opcode() << to_send << std::endl;
#endif	/* !DEBUG */
  m_to_send.push_back(to_send);
}

bool	TCP_protocol::want_send(void) const
{
  return (m_to_send.size() != 0);
}

bool	TCP_protocol::want_recv(void) const
{
  return (true);
}

void	TCP_protocol::send(ITCP_client const &socket)
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

void	TCP_protocol::recv(ITCP_client const &socket)
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
    case ATCP_packet::List_meta_games:
      recv_list_meta_games();
      return;
    case ATCP_packet::Meta_games:
      recv_meta_games();
      return;
    case ATCP_packet::Create_game:
      recv_create_game();
      return;
    case ATCP_packet::Join_game:
      recv_join_game();
      return;
    case ATCP_packet::Message:
      recv_message();
      return;
    case ATCP_packet::List_meta_params:
      recv_list_meta_params();
      return;
    case ATCP_packet::Meta_params:
      recv_meta_params();
      return;
    case ATCP_packet::Change_param:
      recv_change_param();
      return;
    case ATCP_packet::List_meta_sprites:
      recv_list_meta_sprites();
      return;
    case ATCP_packet::Meta_sprites:
      recv_meta_sprites();
      return;
    case ATCP_packet::Take_sprite:
      recv_take_sprite();
      return;
    case ATCP_packet::Give_sprite:
      recv_give_sprite();
      return;
    case ATCP_packet::List_meta_sounds:
      recv_list_meta_sounds();
      return;
    case ATCP_packet::Meta_sounds:
      recv_meta_sounds();
      return;
    case ATCP_packet::Take_sound:
      recv_take_sound();
      return;
    case ATCP_packet::Give_sound:
      recv_give_sound();
      return;
    case ATCP_packet::Ready:
      recv_ready();
      return;
    case ATCP_packet::Start:
      recv_start();
      return;
    case ATCP_packet::End:
      recv_end();
      return;
    case ATCP_packet::Leave:
      recv_leave();
      return;
    }
  throw std::exception();
}

void	TCP_protocol::send_result(ITCP_protocol::Error error)
{
  TCP_packet_send	*to_send = new TCP_packet_send();
  to_send->put(error);
  set_to_send(to_send, ATCP_packet::Result);
}

void	TCP_protocol::recv_result(void)
{
  ITCP_protocol::Error	error;
  m_to_recv.get(error);
  m_callback.result(*this, error);
}

void	TCP_protocol::send_connect(std::string const &login, std::string const &password)
{
  TCP_packet_send	*to_send = new TCP_packet_send();
  to_send->put<uint8_t>(1);
  to_send->put(login);
  to_send->put(password);
  set_to_send(to_send, ATCP_packet::Connect);
}

void	TCP_protocol::recv_connect(void)
{
  std::string	login;
  std::string	password;
  uint8_t	version;

  m_to_recv.get(version);
  m_to_recv.get(login);
  m_to_recv.get(password);
  if (version != 1) // chiant !
    throw std::exception();
  m_callback.connect(*this, login, password);
}

void	TCP_protocol::send_disconnect(void)
{
  TCP_packet_send	*to_send = new TCP_packet_send();
  set_to_send(to_send, ATCP_packet::Disconnect);
}

void	TCP_protocol::recv_disconnect(void)
{
  m_callback.disconnect(*this);
}

void	TCP_protocol::send_ping(void)
{
  TCP_packet_send	*to_send = new TCP_packet_send();
  set_to_send(to_send, ATCP_packet::Ping);
}

void	TCP_protocol::recv_ping(void)
{
  m_callback.ping(*this);
}

void	TCP_protocol::send_pong(void)
{
  TCP_packet_send	*to_send = new TCP_packet_send();
  set_to_send(to_send, ATCP_packet::Pong);
}

void	TCP_protocol::recv_pong(void)
{
  m_callback.pong(*this);
}

void	TCP_protocol::send_list_meta_games(void)
{
 TCP_packet_send	*to_send = new TCP_packet_send();
 set_to_send(to_send, ATCP_packet::List_meta_games);
}

void	TCP_protocol::recv_list_meta_games(void)
{
  m_callback.list_meta_games(*this);
}

void	TCP_protocol::send_meta_games(std::list<ITCP_protocol::Game *> const &games)
{
  TCP_packet_send	*to_send = new TCP_packet_send();

  to_send->put(static_cast<uint8_t>(games.size()));
  for (auto game : games)
    {
      to_send->put(game->name);
      to_send->put(game->owner);
      to_send->put(game->number_player);
      to_send->put(game->number_player_max);
    }
  set_to_send(to_send, ATCP_packet::Meta_games);
}

void	TCP_protocol::recv_meta_games(void)
{
  std::list<ITCP_protocol::Game *>	games;
  uint8_t	size;

  m_to_recv.get(size);
  for (uintmax_t i = 0; i < size; i++)
    {
      ITCP_protocol::Game &game = *new ITCP_protocol::Game({"", "", 0, 0});
      
      m_to_recv.get(game.name);
      m_to_recv.get(game.owner);
      m_to_recv.get(game.number_player);
      m_to_recv.get(game.number_player_max);
      games.push_back(&game);
    }
  m_callback.meta_games(*this, games);
  for (auto game : games)
    delete game;
}

void	TCP_protocol::send_create_game(ITCP_protocol::Game const &game)
{
  TCP_packet_send	*to_send = new TCP_packet_send();
 
  to_send->put(game.name);
  to_send->put(game.owner);
  to_send->put(game.number_player_max);
  set_to_send(to_send, ATCP_packet::Create_game);
}

void	TCP_protocol::recv_create_game(void)
{
  ITCP_protocol::Game game({"", "", 0, 0});
  m_to_recv.get(game.name);
  m_to_recv.get(game.owner);
  m_to_recv.get(game.number_player_max);
  m_callback.create_game(*this, game);
}

void	TCP_protocol::send_join_game(ITCP_protocol::Game const &game)
{
  TCP_packet_send	*to_send = new TCP_packet_send();

  to_send->put(game.name);
  to_send->put(game.owner);
  set_to_send(to_send, ATCP_packet::Join_game);
}

void	TCP_protocol::recv_join_game(void)
{
  ITCP_protocol::Game game({"", "", 0, 0});
  m_to_recv.get(game.name);
  m_to_recv.get(game.owner);
  m_callback.join_game(*this, game);
}

void	TCP_protocol::send_message(std::string const &login, std::string const &message)
{
 TCP_packet_send	*to_send = new TCP_packet_send();
 to_send->put(login);
 to_send->put(message);
 set_to_send(to_send, ATCP_packet::Message);
}

void	TCP_protocol::recv_message(void)
{
  std::string	login;
  std::string	message;
  m_to_recv.get(login);
  m_to_recv.get(message);
  m_callback.message(*this, login, message);
}

void	TCP_protocol::send_list_meta_params(void)
{
  TCP_packet_send	*to_send = new TCP_packet_send();
  set_to_send(to_send, ATCP_packet::List_meta_params);
}

void	TCP_protocol::recv_list_meta_params(void)
{
  m_callback.list_meta_params(*this);
}

void	TCP_protocol::send_meta_params(std::list<ITCP_protocol::Param *> const &params)
{
  TCP_packet_send	*to_send = new TCP_packet_send();
  to_send->put(static_cast<uint8_t>(params.size()));
  for (auto param : params)
    {
      to_send->put(param->name);
      to_send->put(param->value);
    }
  set_to_send(to_send, ATCP_packet::Meta_params);  
}

void	TCP_protocol::recv_meta_params(void)
{
  std::list<ITCP_protocol::Param *>	params;
  uint8_t	size;

  m_to_recv.get(size);
  for (uintmax_t i = 0; i < size; i++)
    {
      ITCP_protocol::Param &param = *new ITCP_protocol::Param({"", ""});

      m_to_recv.get(param.name);
      m_to_recv.get(param.value);
      params.push_back(&param);
    }
  m_callback.meta_params(*this, params);
  for (auto param : params)
    {
      delete param;
    }
}

void	TCP_protocol::send_change_param(ITCP_protocol::Param const &param)
{
  TCP_packet_send	*to_send = new TCP_packet_send();
  to_send->put(param.name);
  to_send->put(param.value);
  set_to_send(to_send, ATCP_packet::Change_param);
}

void	TCP_protocol::recv_change_param(void)
{
  ITCP_protocol::Param	param({"", ""});
  m_to_recv.get(param.name);
  m_to_recv.get(param.value);
  m_callback.change_param(*this, param);
}

void	TCP_protocol::send_list_meta_sprites(void)
{
  TCP_packet_send	*to_send = new TCP_packet_send();
  set_to_send(to_send, ATCP_packet::List_meta_sprites);
}

void	TCP_protocol::recv_list_meta_sprites(void)
{
  m_callback.list_meta_sprites(*this);
}

void	TCP_protocol::send_meta_sprites(std::list<ITCP_protocol::Sprite *> const &sprites)
{
  TCP_packet_send	*to_send = new TCP_packet_send();
  to_send->put(static_cast<uint8_t>(sprites.size()));
  for (auto sprite : sprites)
    {
      to_send->put(sprite->name);
      to_send->put(sprite->checksome);
      to_send->put(sprite->id);
      to_send->put(sprite->size);
    }
  set_to_send(to_send, ATCP_packet::Meta_sprites);
}

void	TCP_protocol::recv_meta_sprites(void)
{
  std::list<ITCP_protocol::Sprite *>	sprites;
  uint8_t	size;

  m_to_recv.get(size);
  for (uintmax_t i = 0; i < size; i++)
    {
      ITCP_protocol::Sprite &sprite = *new ITCP_protocol::Sprite({"", "", 0, nullptr, 0});

      m_to_recv.get(sprite.name);
      m_to_recv.get(sprite.checksome);
      m_to_recv.get(sprite.id);
      m_to_recv.get(sprite.size);
      sprites.push_back(&sprite);
    }
  m_callback.meta_sprites(*this, sprites);
  for (auto sprite : sprites)
    {
      delete sprite;
    }
}

void	TCP_protocol::send_take_sprite(ITCP_protocol::Sprite const &sprite)
{
  TCP_packet_send	*to_send = new TCP_packet_send();
  to_send->put(sprite.name);
  to_send->put(sprite.id);
  set_to_send(to_send, ATCP_packet::Take_sprite);
}

void	TCP_protocol::recv_take_sprite(void)
{
  ITCP_protocol::Sprite	sprite({"", "", 0, nullptr, 0});
  m_to_recv.get(sprite.name);
  m_to_recv.get(sprite.id);
  m_callback.take_sprite(*this, sprite);
}

void	TCP_protocol::send_give_sprite(ITCP_protocol::Sprite const &sprite)
{
  TCP_packet_send	*to_send = new TCP_packet_send();
  to_send->put(sprite.name);
  to_send->put(sprite.id);
  to_send->put(sprite.size);
  for (uintmax_t i = 0; i < sprite.size; i++)
    to_send->put(sprite.data[i]);
  set_to_send(to_send, ATCP_packet::Give_sprite);
}

void	TCP_protocol::recv_give_sprite(void)
{
  ITCP_protocol::Sprite	sprite({"", "", 0, nullptr, 0});
  uint8_t	*data;
  m_to_recv.get(sprite.name);
  m_to_recv.get(sprite.id);
  m_to_recv.get(sprite.size);
  data = new uint8_t[sprite.size];
  sprite.data = data;
  for (uintmax_t i = 0; i < sprite.size; i++)
    m_to_recv.get(data[i]);
  m_callback.give_sprite(*this, sprite);
  delete[] sprite.data;
}

void	TCP_protocol::send_list_meta_sounds(void)
{
  TCP_packet_send	*to_send = new TCP_packet_send();
  set_to_send(to_send, ATCP_packet::List_meta_sounds);
}

void	TCP_protocol::recv_list_meta_sounds(void)
{
  m_callback.list_meta_sounds(*this);
}

void	TCP_protocol::send_meta_sounds(std::list<ITCP_protocol::Sound *> const &sounds)
{
  TCP_packet_send	*to_send = new TCP_packet_send();
  to_send->put(static_cast<uint8_t>(sounds.size()));
  for (auto sound : sounds)
    {
      to_send->put(sound->name);
      to_send->put(sound->id);
      to_send->put(sound->checksome);
      to_send->put(sound->size);      
    }
  set_to_send(to_send, ATCP_packet::Meta_sounds);
}

void	TCP_protocol::recv_meta_sounds(void)
{
  std::list<ITCP_protocol::Sound *>	sounds;
  uint8_t	size;

  m_to_recv.get(size);
  for (uintmax_t i = 0; i < size; i++)
    {
      ITCP_protocol::Sound &sound = *new ITCP_protocol::Sound({"", "", 0, nullptr, 0});

      m_to_recv.get(sound.name);
      m_to_recv.get(sound.checksome);
      m_to_recv.get(sound.id);
      m_to_recv.get(sound.size);
      sounds.push_back(&sound);
    }
  m_callback.meta_sounds(*this, sounds);
  for (auto sound : sounds)
    {
      delete sound;
    }
}

void	TCP_protocol::send_take_sound(ITCP_protocol::Sound const &sound)
{
  TCP_packet_send	*to_send = new TCP_packet_send();
  to_send->put(sound.name);
  to_send->put(sound.id);
  set_to_send(to_send, ATCP_packet::Take_sound);
}

void	TCP_protocol::recv_take_sound(void)
{
  ITCP_protocol::Sound	sound({"", "", 0, nullptr, 0});
  m_to_recv.get(sound.name);
  m_to_recv.get(sound.id);
  m_callback.take_sound(*this, sound);
}

void	TCP_protocol::send_give_sound(ITCP_protocol::Sound const &sound)
{
  TCP_packet_send	*to_send = new TCP_packet_send();
  to_send->put(sound.name);
  to_send->put(sound.id);
  to_send->put(sound.size);
  for (uintmax_t i = 0; i < sound.size; i++)
    to_send->put((&sound.data)[i]);
  set_to_send(to_send, ATCP_packet::Give_sound);
}

void	TCP_protocol::recv_give_sound(void)
{
  ITCP_protocol::Sound	sound({"", "", 0, nullptr, 0});
  uint8_t	*data;
  m_to_recv.get(sound.name);
  m_to_recv.get(sound.id);
  m_to_recv.get(sound.size);
  data = new uint8_t[sound.size];
  for (uintmax_t i = 0; i < sound.size; i++)
    m_to_recv.get(data[i]);
  sound.data = data;
  m_callback.give_sound(*this, sound);
  delete[] sound.data;
}

void	TCP_protocol::send_ready(bool ready)
{
  TCP_packet_send	*to_send = new TCP_packet_send();
  to_send->put(ready);
  set_to_send(to_send, ATCP_packet::Ready);
}

void	TCP_protocol::recv_ready(void)
{
  bool	ready;
  m_to_recv.get(ready);
  m_callback.ready(*this, ready);
}

void	TCP_protocol::send_start(uint8_t second, uint16_t port)
{
  TCP_packet_send	*to_send = new TCP_packet_send();
  to_send->put(second);
  to_send->put(port);
  set_to_send(to_send, ATCP_packet::Start);
}

void	TCP_protocol::recv_start(void)
{
  uint8_t	second;
  uint16_t	port;
  m_to_recv.get(second);
  m_to_recv.get(port);
  m_callback.start(*this, second, port);
}

void	TCP_protocol::send_end(uint64_t score, bool winner)
{  
  TCP_packet_send	*to_send = new TCP_packet_send();
  // TCP_packet_send	*to_send = new TCP_packet_send();
  // to_send->put(score);
  // to_send->put(winner);
  // set_to_send(to_send, ATCP_packet::End);
  test(to_send, ATCP_packet::End, score, winner);
}

void	TCP_protocol::recv_end(void)
{
  uint64_t	score;
  bool	winner;
  m_to_recv.get(score);
  m_to_recv.get(winner);
  m_callback.end(*this, score, winner);
}

void	TCP_protocol::send_leave(void)
{
  TCP_packet_send	*to_send = new TCP_packet_send();
  test(to_send, ATCP_packet::Leave);
}

void	TCP_protocol::recv_leave(void)
{
  m_callback.leave(*this);
}
