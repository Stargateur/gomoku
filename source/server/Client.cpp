#include	"Client.hpp"

Client::Client(ITCP_client *itcp_client, std::string *login) :
	m_itcp_client(itcp_client),
	m_login(login),
	m_wait_pong(false),
	m_last(std::chrono::steady_clock::now()),
	m_error(0)
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

void	Client::add_error(void)
{
	m_error++;
}

uintmax_t	Client::get_error(void) const
{
	return (m_error);
}

std::ostream	&operator<<(std::ostream &os, Client const &client)
{
	return os << (client.get_login() != NULL ? *client.get_login() : "Unknow Client");
}