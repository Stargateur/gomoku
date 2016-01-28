//
// Client.cpp for Client in /home/plasko_a/projet/gomoku
//
// Made by Antoine Plaskowski
// Login   <antoine.plaskowski@epitech.eu>
//
// Started on  Tue Jan 26 18:05:03 2016 Antoine Plaskowski
// Last update Thu Jan 28 09:32:09 2016 Antoine Plaskowski
//

#include	"Client.hpp"

Client::~Client(void)
{
    delete itcp_client;
    delete login;
    delete last;
}
