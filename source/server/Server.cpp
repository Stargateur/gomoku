//
// Server.cpp for Server in /home/plasko_a/projet/gomoku/source
// 
// Made by Antoine Plaskowski
// Login   <antoine.plaskowski@epitech.eu>
// 
// Started on  Tue Jan 26 17:50:03 2016 Antoine Plaskowski
// Last update Wed Jan 27 11:32:19 2016 Antoine Plaskowski
//

#include	"Server.hpp"

Server::Server(void) :
  m_itcp_server(new TCP_server("4242")),
  m_istandard(new Standard(IStandard::In)),
  m_itcp_protocols(),
  m_iselect(new Select())
{
}

Server::~Server(void)
{
  delete m_itcp_server;
  delete m_istandard;
  for (auto itcp_protocol : m_itcp_protocols)
    delete itcp_protocol;
  delete m_iselect;
}

void	Server::run(void)
{
  bool  g_keep_running = true;

  while (g_keep_running == true)
    {
      m_iselect->reset();

      m_iselect->want_read(*m_istandard);

      m_iselect->want_read(*m_itcp_server);

      for (auto itcp_protocol : m_itcp_protocols)
	{
	  Client &client = *itcp_protocol->get_data();

	  if (itcp_protocol->want_recv())
	    m_iselect->want_read(*client.m_itcp_client);

	  if (itcp_protocol->want_send())
	    m_iselect->want_write(*client.m_itcp_client);
	}
      
      m_iselect->select();

      if (m_iselect->can_read(*m_istandard))
	{
	  uint8_t       buffer[42];

	  if (m_istandard->read(buffer[0], 42) == 0)
	    g_keep_running = false;
	}
      
      if (m_iselect->can_read(*m_itcp_server))
	m_itcp_protocols.push_back(new TCP_protocol<Client>(this, new Client(&m_itcp_server->accept())));
      for (auto it = m_itcp_protocols.begin(); it != m_itcp_protocols.end();)
	{
	  Client &client = *(*it)->get_data();

	  try
	    {
	      if (m_iselect->can_read(*client.m_itcp_client))
		(*it)->recv(*client.m_itcp_client);

	      if (m_iselect->can_write(*client.m_itcp_client))
		(*it)->send(*client.m_itcp_client);

	      it++;
	    }
	  catch (...)
	    {
	      delete (*it)->get_data();
	      delete (*it);
	      it = m_itcp_protocols.erase(it);
	    }
	}
    }
}

void	Server::result(ITCP_protocol<Client> &itcp_protocol, typename ITCP_protocol<Client>::Error error)
{
  std::cout << error << std::endl;
}

void	Server::connect(ITCP_protocol<Client> &itcp_protocol, uint8_t version, std::string *login, std::string *password)
{
  if (version != itcp_protocol.get_version())
    throw std::logic_error("Wrong version");
  std::cout << *login << " " << *password << std::endl;
  if (*login != *password)
    throw std::logic_error("Wrong login and/or password");
  delete itcp_protocol.get_data()->m_login;
  itcp_protocol.get_data()->m_login = login;
  delete password;
}

void	Server::disconnect(ITCP_protocol<Client> &itcp_protocol)
{
  throw std::logic_error("disconnect");
}

void	Server::ping(ITCP_protocol<Client> &itcp_protocol)
{
  itcp_protocol.send_pong();
}

void	Server::pong(ITCP_protocol<Client> &itcp_protocol)
{
}

void	Server::create_game(ITCP_protocol<Client> &itcp_protocol, typename ITCP_protocol<Client>::Game *game)
{
}

void	Server::join_game(ITCP_protocol<Client> &itcp_protocol, typename ITCP_protocol<Client>::Game *game)
{
}

void	Server::leave_game(ITCP_protocol<Client> &itcp_protocol)
{
}

void	Server::put_stone_game(ITCP_protocol<Client> &itcp_protocol, typename ITCP_protocol<Client>::Game_stone *stone)
{
}

void	Server::change_param_game(ITCP_protocol<Client> &itcp_protocol, typename ITCP_protocol<Client>::Game_param *param)
{
}

void	Server::list_param_game(ITCP_protocol<Client> &itcp_protocol, std::list<typename ITCP_protocol<Client>::Game_param *> *params)
{
}

void	Server::game_created(ITCP_protocol<Client> &itcp_protocol, typename ITCP_protocol<Client>::Game *game)
{
}

void	Server::game_player_joined(ITCP_protocol<Client> &itcp_protocol, std::string *name)
{
}

void	Server::game_player_left(ITCP_protocol<Client> &itcp_protocol, std::string *name)
{
}

void	Server::game_param_changed(ITCP_protocol<Client> &itcp_protocol, typename ITCP_protocol<Client>::Game_param *param)
{
}

void	Server::game_stone_put(ITCP_protocol<Client> &itcp_protocol, typename ITCP_protocol<Client>::Game_stone *stone)
{
}

void	Server::game_deleted(ITCP_protocol<Client> &itcp_protocol, typename ITCP_protocol<Client>::Game *game)
{
}

void	Server::start_game(ITCP_protocol<Client> &itcp_protocol)
{
}

void	Server::ready_game(ITCP_protocol<Client> &itcp_protocol, bool ready)
{
}

void	Server::result_game(ITCP_protocol<Client> &itcp_protocol, typename ITCP_protocol<Client>::Game_result *game_result)
{
}

void	Server::message(ITCP_protocol<Client> &itcp_protocol, typename ITCP_protocol<Client>::Message *message)
{
}
