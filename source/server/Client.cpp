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

Client::Client(ITCP_client *itcp_client, std::string *login, bool wait_pong) :
	m_itcp_client(itcp_client),
	m_login(login),
	m_wait_pong(wait_pong)
{
}

Client::~Client(void)
{
    delete m_itcp_client;
    delete m_login;
}

void	Client::set_itcp_client(ITCP_client *itcp_client)
{
	delete m_itcp_client;
	m_itcp_client = itcp_client;
}

ITCP_client const	*Client::get_itcp_client(void) const
{
	return (m_itcp_client);
}

ITCP_client	*Client::get_itcp_client(void)
{
	return (m_itcp_client);
}

void	Client::set_login(std::string *login)
{
	delete m_login;
	m_login = login;
}

std::string const	*Client::get_login(void) const
{
	return (m_login);
}

std::string	*Client::get_login(void)
{
	return (m_login);
}

std::chrono::steady_clock::time_point const	&Client::get_last(void) const
{
	return (m_last);
}

std::chrono::steady_clock::time_point	&Client::get_last(void)
{
	return (m_last);
}

void	Client::set_wait_pong(bool wait_pong)
{
	m_wait_pong = wait_pong;
}

bool	Client::get_wait_pong(void) const
{
	return (m_wait_pong);
}