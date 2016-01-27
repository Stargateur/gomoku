//
// Client.cpp for Client in /home/plasko_a/projet/gomoku
// 
// Made by Antoine Plaskowski
// Login   <antoine.plaskowski@epitech.eu>
// 
// Started on  Tue Jan 26 18:05:03 2016 Antoine Plaskowski
// Last update Tue Jan 26 18:18:09 2016 Antoine Plaskowski
//

#include	"Client.hpp"

Client::Client(ITCP_client *itcp_client) :
  m_itcp_client(itcp_client)
{
}

Client::~Client(void)
{
  delete m_itcp_client;
}
