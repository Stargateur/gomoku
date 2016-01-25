//
// UDP_protocol.cpp for UDP_protocol in /home/plasko_a/projet/cplusplus/rtype
// 
// Made by Antoine Plaskowski
// Login   <antoine.plaskowski@epitech.eu>
// 
// Started on  Sun Dec  6 03:40:34 2015 Antoine Plaskowski
// Last update Sat Dec 26 15:48:00 2015 Antoine Plaskowski
//

#include	<algorithm>
#include	"UDP_protocol.hpp"

UDP_protocol::UDP_protocol(IUDP_protocol::Callback &callback) :
  m_callback(callback)
{
}

UDP_protocol::~UDP_protocol(void)
{
  for (auto elem : m_to_send)
    delete elem;
  for (auto elem : m_to_sendto)
    delete elem;
}

// void	UDP_protocol::set_callback(IUDP_protocol::Callback &callback)
// {
//   m_callback = &callback;
// }

void	UDP_protocol::set_to_send(UDP_packet_send *to_send, AUDP_packet::Opcode opcode)
{
  to_send->set_opcode(opcode);
  m_to_send.push_back(to_send);
}

void	UDP_protocol::set_to_send(m_sendto *to_send, AUDP_packet::Opcode opcode, IUDP_server::u_sockaddr const &sockaddr, socklen_t len)
{
  std::get<0>(*to_send).set_opcode(opcode);
  // copier
  m_to_sendto.push_back(to_send);
}

bool	UDP_protocol::want_send(void) const
{
  return (m_to_send.size() != 0);
}

bool	UDP_protocol::want_recv(void) const
{
  return (true);
}

bool	UDP_protocol::want_sendto(void) const
{
  return (m_to_sendto.size() != 0);
}

bool	UDP_protocol::want_recvfrom(void) const
{
  return (true);
}

void	UDP_protocol::send(IUDP_client const &socket)
{
  UDP_packet_send	*to_send = m_to_send.front();
  m_to_send.pop_front();

  to_send->send(socket);
  delete to_send;
}

void	UDP_protocol::sendto(IUDP_server const &socket)
{
  m_sendto	*to_send = m_to_sendto.front();
  m_to_sendto.pop_front();

  std::get<0>(*to_send).sendto(socket, std::get<1>(*to_send), std::get<2>(*to_send));
  delete to_send;
}

void	UDP_protocol::recv(IUDP_client const &socket)
{
  m_to_recv.recv(socket);
  switch (m_to_recv.get_opcode())
    {
    case AUDP_packet::Sprites:
      recv_sprites();
      return;
    case AUDP_packet::Sounds:
      recv_sounds();
      return;
    case AUDP_packet::Input:
      recv_input();
      return;
     }
  throw std::exception();
}

void	UDP_protocol::recvfrom(IUDP_server const &socket)
{
  IUDP_server::u_sockaddr	sockaddr;
  socklen_t	len;

  m_to_recv.recvfrom(socket, sockaddr, len);
  switch (m_to_recv.get_opcode())
    {
    case AUDP_packet::Sprites:
      recv_sprites(sockaddr, len);
      return;
    case AUDP_packet::Sounds:
      recv_sounds(sockaddr, len);
      return;
    case AUDP_packet::Input:
      recv_input(sockaddr, len);
      return;
     }
  throw std::exception();
}

void	UDP_protocol::send_sprites(std::list<IUDP_protocol::Sprite *> const &sprites)
{
  UDP_packet_send	*to_send = new UDP_packet_send();

  to_send->put(static_cast<uint8_t>(sprites.size()));
  for (auto sprite : sprites)
    {
      to_send->put(sprite->id);
      to_send->put(sprite->x);
      to_send->put(sprite->y);
      to_send->put(sprite->rotation);
    }
  set_to_send(to_send, AUDP_packet::Sprites);
}

void	UDP_protocol::recv_sprites(void)
{
  std::list<IUDP_protocol::Sprite *>      sprites;
  uint8_t       size;

  m_to_recv.get(size);
  for (uintmax_t i = 0; i < size; i++)
    {
      IUDP_protocol::Sprite *sprite = new IUDP_protocol::Sprite();

      m_to_recv.get(sprite->id);
      m_to_recv.get(sprite->x);
      m_to_recv.get(sprite->y);
      m_to_recv.get(sprite->rotation);
      sprites.push_back(sprite);
    }
  m_callback.sprites(*this, sprites);
  for (auto sprite : sprites)
    {
      delete sprite;
    }
}

void	UDP_protocol::send_sounds(std::list<IUDP_protocol::Sound *> const &sounds)
{
  UDP_packet_send	*to_send = new UDP_packet_send();

  to_send->put(static_cast<uint8_t>(sounds.size()));
  for (auto sound : sounds)
    {
      to_send->put(sound->id);
    }
  set_to_send(to_send, AUDP_packet::Sounds);
}

void	UDP_protocol::recv_sounds(void)
{
  std::list<IUDP_protocol::Sound *>      sounds;
  uint8_t       size;

  m_to_recv.get(size);
  for (uintmax_t i = 0; i < size; i++)
    {
      IUDP_protocol::Sound *sound = new IUDP_protocol::Sound();

      m_to_recv.get(sound->id);
      sounds.push_back(sound);
    }
  m_callback.sounds(*this, sounds);
  for (auto sound : sounds)
    {
      delete sound;
    }
}

void	UDP_protocol::send_input(std::string const &login, IUDP_protocol::Input const &input)
{
  UDP_packet_send	*to_send = new UDP_packet_send();

  to_send->put(login);
  to_send->put(input.up);
  to_send->put(input.down);
  to_send->put(input.left);
  to_send->put(input.right);
  to_send->put(input.shot);
  to_send->put(input.bomb);
  set_to_send(to_send, AUDP_packet::Input);
}

void	UDP_protocol::recv_input(void)
{
  IUDP_protocol::Input	input;
  std::string	login;

  m_to_recv.get(login);
  m_to_recv.get(input.up);
  m_to_recv.get(input.down);
  m_to_recv.get(input.left);
  m_to_recv.get(input.right);
  m_to_recv.get(input.shot);
  m_to_recv.get(input.bomb);
  m_callback.input(*this, login, input);
}

void	UDP_protocol::send_sprites(std::list<IUDP_protocol::Sprite *> const &sprites, IUDP_server::u_sockaddr const &sockaddr, socklen_t len)
{
  m_sendto	*to_send = new m_sendto();

  std::get<0>(*to_send).put(static_cast<uint8_t>(sprites.size()));
  for (auto sprite : sprites)
    {
      std::get<0>(*to_send).put(sprite->id);
      std::get<0>(*to_send).put(sprite->x);
      std::get<0>(*to_send).put(sprite->y);
      std::get<0>(*to_send).put(sprite->rotation);
    }
  set_to_send(to_send, AUDP_packet::Sprites, sockaddr, len);
}

void	UDP_protocol::recv_sprites(IUDP_server::u_sockaddr const &sockaddr, socklen_t len)
{
  std::list<IUDP_protocol::Sprite *>      sprites;
  uint8_t       size;

  m_to_recv.get(size);
  for (uintmax_t i = 0; i < size; i++)
    {
      IUDP_protocol::Sprite *sprite = new IUDP_protocol::Sprite();

      m_to_recv.get(sprite->id);
      m_to_recv.get(sprite->x);
      m_to_recv.get(sprite->y);
      m_to_recv.get(sprite->rotation);
      sprites.push_back(sprite);
    }
  m_callback.sprites(*this, sprites, sockaddr, len);
  for (auto sprite : sprites)
    {
      delete sprite;
    }
}

void	UDP_protocol::send_sounds(std::list<IUDP_protocol::Sound *> const &sounds, IUDP_server::u_sockaddr const &sockaddr, socklen_t len)
{
  m_sendto	*to_send = new m_sendto();

  std::get<0>(*to_send).put(static_cast<uint8_t>(sounds.size()));
  for (auto sound : sounds)
    {
      std::get<0>(*to_send).put(sound->id);
    }
  set_to_send(to_send, AUDP_packet::Sounds, sockaddr, len);
}

void	UDP_protocol::recv_sounds(IUDP_server::u_sockaddr const &sockaddr, socklen_t len)
{
  std::list<IUDP_protocol::Sound *>      sounds;
  uint8_t       size;

  m_to_recv.get(size);
  for (uintmax_t i = 0; i < size; i++)
    {
      IUDP_protocol::Sound *sound = new IUDP_protocol::Sound();

      m_to_recv.get(sound->id);
      sounds.push_back(sound);
    }
  m_callback.sounds(*this, sounds, sockaddr, len);
  for (auto sound : sounds)
    {
      delete sound;
    }
}

void	UDP_protocol::send_input(std::string const &login, IUDP_protocol::Input const &input, IUDP_server::u_sockaddr const &sockaddr, socklen_t len)
{
  m_sendto	*to_send = new m_sendto();

  std::get<0>(*to_send).put(login);
  std::get<0>(*to_send).put(input.up);
  std::get<0>(*to_send).put(input.down);
  std::get<0>(*to_send).put(input.left);
  std::get<0>(*to_send).put(input.right);
  std::get<0>(*to_send).put(input.shot);
  std::get<0>(*to_send).put(input.bomb);
  set_to_send(to_send, AUDP_packet::Input, sockaddr, len);
}

void	UDP_protocol::recv_input(IUDP_server::u_sockaddr const &sockaddr, socklen_t len)
{
  IUDP_protocol::Input	input;
  std::string	login;

  m_to_recv.get(login);
  m_to_recv.get(input.up);
  m_to_recv.get(input.down);
  m_to_recv.get(input.left);
  m_to_recv.get(input.right);
  m_to_recv.get(input.shot);
  m_to_recv.get(input.bomb);
  m_callback.input(*this, login, input, sockaddr, len);
}
