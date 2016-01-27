//
// Client.cpp for Client in /home/plasko_a/projet/gomoku
// 
// Made by Antoine Plaskowski
// Login   <antoine.plaskowski@epitech.eu>
// 
// Started on  Tue Jan 26 18:05:03 2016 Antoine Plaskowski
// Last update Wed Jan 27 18:38:02 2016 Antoine Plaskowski
//

#include	"Client.hpp"

Client::Client(void) :
  m_itcp_client(nullptr),
  m_login(nullptr),
  m_last(nullptr),
  m_wait_pong(false)
{
}

Client::~Client(void)
{
  delete m_itcp_client;
  delete m_login;
  delete m_last;
}
