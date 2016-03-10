#include    <thread>
#include	"TCP_protocol.hpp"
#include	"TCP_server.hpp"
#include	"TCP_client.hpp"
#include	"Server.hpp"
#include    "Utils.hpp"

Server::Server(std::string const &port) try :
    Server(new TCP_server(port))
{
}
catch (...)
{
}

Server::Server(ITCP_server *itcp_server) try :
    m_itcp_server(itcp_server),
    m_iselect(new Select()),
    m_timeout(5)
{
}
catch (...)
{
    delete itcp_server;
}

Server::~Server(void)
{
    delete m_itcp_server;
    for (iprotocol::ITCP_protocol<Client> *itcp_protocol : m_itcp_protocols)
        delete itcp_protocol;
    for (Game *game : m_games)
        delete game;
    delete m_iselect;
}

void    Server::pre_run(void)
{
    m_iselect->reset();

    m_iselect->want_read(*m_itcp_server);
    for (iprotocol::ITCP_protocol<Client> *itcp_protocol : m_itcp_protocols)
    {
        Client &client = *itcp_protocol->get_data();

        if (itcp_protocol->want_recv())
            m_iselect->want_read(*client.get_itcp_client());

        if (itcp_protocol->want_send())
            m_iselect->want_write(*client.get_itcp_client());
    }

	auto disconnect = m_disconnecteds.begin();
	while (disconnect != m_disconnecteds.end())
	{
		iprotocol::ITCP_protocol<Client> *itcp_protocol = *disconnect;
		Client &client = *itcp_protocol->get_data();

		if (itcp_protocol->want_send())
		{
			m_iselect->want_write(*client.get_itcp_client());
			disconnect++;
		}
		else
		{
			disconnect = m_disconnecteds.erase(disconnect);
			delete itcp_protocol;
            #ifndef NDEBUG
            std::cerr << "SERVER : DELETE CLIENT" << std::endl;
            #endif
		}
	}

    for (Game *game : m_games)
    {
        game->pre_run(*m_iselect);
    }
}

void	Server::run(void)
{
    m_iselect->select();

    if (m_iselect->can_read(*m_itcp_server))
    {
		try
		{
			m_iselect->reset_read(*m_itcp_server);
			Client	*client = new Client(&m_itcp_server->accept(), nullptr);
			#ifndef NDEBUG
			std::cerr << "SERVER : NEW CLIENT" << std::endl;
			#endif
			m_itcp_protocols.push_back(new iprotocol::TCP_protocol<Client>(this, client));
		}
		catch (std::exception &e)
		{
			std::cerr << e.what() << std::endl;
		}
    }
    auto disconnect = m_disconnecteds.begin();
    while (disconnect != m_disconnecteds.end())
    {
        iprotocol::ITCP_protocol<Client> *itcp_protocol = *disconnect;
        try
        {
			Client &client = *itcp_protocol->get_data();
            if (m_iselect->can_write(*client.get_itcp_client()))
            {
                m_iselect->reset_write(*client.get_itcp_client());
                itcp_protocol->send(*client.get_itcp_client());
            }
            else
                throw AServer_exception();
            disconnect++;
        }
        catch (std::exception &e)
        {
            std::cerr << e.what() << std::endl;
            disconnect = m_disconnecteds.erase(disconnect);
            delete itcp_protocol;
            #ifndef NDEBUG
            std::cerr << "SERVER : DELETE CLIENT" << std::endl;
            #endif
        }
    }
    for (auto it = m_itcp_protocols.begin(); it != m_itcp_protocols.end();)
    {
        iprotocol::ITCP_protocol<Client> *itcp_protocol = *it;
        Client &client = *itcp_protocol->get_data();
        try
        {
            if (m_iselect->can_read(*client.get_itcp_client()))
            {
                itcp_protocol->get_data()->get_last() = std::chrono::steady_clock::now();
                m_iselect->reset_read(*client.get_itcp_client());
                itcp_protocol->recv(*client.get_itcp_client());
            }
            else
                Utils::timeout(*itcp_protocol, m_timeout);

            if (m_iselect->can_write(*client.get_itcp_client()))
            {
                m_iselect->reset_write(*client.get_itcp_client());
                itcp_protocol->send(*client.get_itcp_client());
            }
            it++;
        }
        catch (Server_exception_client_transfer &e)
        {
            it = m_itcp_protocols.erase(it);
            e.m_game->add_player(itcp_protocol);
        }
        catch (AServer_exception &e)
        {
            std::cerr << e.what() << std::endl;
            it = m_itcp_protocols.erase(it);
            m_disconnecteds.push_back(itcp_protocol);
        }
        catch (std::exception &e)
        {
            std::cerr << e.what() << std::endl;
            it = m_itcp_protocols.erase(it);
            delete itcp_protocol;
        }
    }
    auto it_game = m_games.begin();
    while (it_game != m_games.end())
    {
        Game *game = *it_game;
        try
        {
            game->run(*m_iselect);
            it_game++;
        }
        catch (Game_exception_client_transfer &e)
        {
            e.m_client->set_callback(this);
            m_itcp_protocols.push_back(e.m_client);
            it_game++;
        }
        catch (std::exception &e)
        {
			#ifndef NDEBUG
			std::cerr << "SERVER : DELETE GAME" << std::endl;
			#endif
            it_game = m_games.erase(it_game);
            std::cerr << e.what() << std::endl;
            for (auto it = game->get_players().begin(); it != game->get_players().end(); it = game->get_players().erase(it))
            {
                (*it)->set_callback(this);
                m_itcp_protocols.push_back(*it);
            }
			for (iprotocol::ITCP_protocol<Client> *itcp_protocol : m_itcp_protocols)
                game->send_game_delete(*itcp_protocol);
            for (Game *game_it : m_games)
                for (iprotocol::ITCP_protocol<Client> *game_player_it : game_it->get_players())
                    game->send_game_delete(*game_player_it);
            delete game;
        }
    }
}

void	Server::result(iprotocol::ITCP_protocol<Client> &itcp_protocol, iprotocol::Error error)
{
    if (itcp_protocol.get_data()->get_login() != nullptr)
        std::cout << itcp_protocol.get_data()->get_login();
    else
        std::cout << "Unknow client";
    std::cout << " has send this error " << error << std::endl;
}

void	Server::connect(iprotocol::ITCP_protocol<Client> &itcp_protocol, uint8_t version, std::string *login, std::string *password)
{
    if (version != itcp_protocol.get_version())
    {
        delete login;
        delete password;
        itcp_protocol.send_result(iprotocol::Error::Wrong_version);
		throw AServer_exception();
    }
    if (*login != *password)
    {
        delete login;
        delete password;
        itcp_protocol.send_result(iprotocol::Error::Wrong_password);
        throw AServer_exception();
    }
    for (iprotocol::ITCP_protocol<Client> *it_itcp_protocol : m_itcp_protocols)
    {
        Client *client = it_itcp_protocol->get_data();

        if (client->get_login() != nullptr)
        {
            if (*client->get_login() == *login)
            {
                delete login;
                delete password;
                itcp_protocol.send_result(iprotocol::Error::Login_already_use);
                throw AServer_exception();
            }
        }
    }
    for (Game *game : m_games)
        for (iprotocol::ITCP_protocol<Client> *it_itcp_protocol : game->get_players())
        {
            Client *client = it_itcp_protocol->get_data();

            if (client->get_login() != nullptr)
            {
                if (*client->get_login() == *login)
                {
                    delete login;
                    delete password;
                    itcp_protocol.send_result(iprotocol::Error::Login_already_use);
                    throw AServer_exception();
                }
            }            
        }
    itcp_protocol.get_data()->set_login(login);
    for (Game *game : m_games)
        game->send_game_create(itcp_protocol);
    delete password;
}

void	Server::disconnect(iprotocol::ITCP_protocol<Client> &itcp_protocol)
{
    itcp_protocol.send_result(iprotocol::Error::Disconnected);
    throw Server_exception_client_disconnected();
}

void	Server::ping(iprotocol::ITCP_protocol<Client> &itcp_protocol)
{
    itcp_protocol.send_pong();
}

void	Server::pong(iprotocol::ITCP_protocol<Client> &itcp_protocol)
{
    Client	&client = *itcp_protocol.get_data();

    client.set_wait_pong(false);
}

void	Server::game_create(iprotocol::ITCP_protocol<Client> &itcp_protocol, iprotocol::Game *game_info)
{
    Client *client = itcp_protocol.get_data();
    if (client->get_login() == nullptr)
    {
        delete game_info->name;
        delete game_info;
        itcp_protocol.send_result(iprotocol::Error::Not_connected);
		throw AServer_exception();
    }
    for (Game *game_it : m_games)
        if (game_it->get_name() == *game_info->name)
            {
                delete game_info->name;
                delete game_info;
				itcp_protocol.send_result(iprotocol::Error::Game_already_exist);
				throw AServer_exception();
            }
    Game	*game = new Game(*this, game_info->name);

    delete game_info;
    for (iprotocol::ITCP_protocol<Client> *it : m_itcp_protocols)
        game->send_game_create(*it);        
    for (Game *it_game : m_games)
        for (iprotocol::ITCP_protocol<Client> *it : it_game->get_players())
            game->send_game_create(*it);
    m_games.push_back(game);
    throw Server_exception_client_transfer(game);
}

void    Server::game_delete(iprotocol::ITCP_protocol<Client> &itcp_protocol, iprotocol::Game *game)
{
    delete game->name;
    delete game;
    itcp_protocol.send_result(iprotocol::Error::Packet_not_allowed);
    throw AServer_exception();
}

void	Server::game_join(iprotocol::ITCP_protocol<Client> &itcp_protocol, iprotocol::Game *game_info)
{
    Client *client = itcp_protocol.get_data();
    if (client->get_login() == nullptr)
    {
        delete game_info->name;
        delete game_info;
        itcp_protocol.send_result(iprotocol::Error::Not_connected);
		throw AServer_exception();
    }
    for (Game *game : m_games)
        if (*game_info->name == game->get_name())
        {
            delete game_info->name;
            delete game_info;
            throw Server_exception_client_transfer(game);
        }
    delete game_info->name;
    delete game_info;
	itcp_protocol.send_result(iprotocol::Error::Game_already_exist);
}

void	Server::game_leave(iprotocol::ITCP_protocol<Client> &itcp_protocol)
{
    itcp_protocol.send_result(iprotocol::Error::Packet_not_allowed);
	throw AServer_exception();
}

void    Server::game_stone_put(iprotocol::ITCP_protocol<Client> &itcp_protocol, iprotocol::Game_stone *stone)
{
    delete stone;
    itcp_protocol.send_result(iprotocol::Error::Packet_not_allowed);
    throw AServer_exception();
}

void	Server::game_param(iprotocol::ITCP_protocol<Client> &itcp_protocol, iprotocol::Game_param *param)
{
    delete param;
    itcp_protocol.send_result(iprotocol::Error::Not_in_game);
	throw AServer_exception();
}

void    Server::game_player_param(iprotocol::ITCP_protocol<Client> &itcp_protocol, iprotocol::Game_player_param *param)
{
    delete param;
    itcp_protocol.send_result(iprotocol::Error::Not_in_game);
	throw AServer_exception();
}

void	Server::game_player_join(iprotocol::ITCP_protocol<Client> &itcp_protocol, std::string *name)
{
    delete name;
    itcp_protocol.send_result(iprotocol::Error::Packet_not_allowed);
	throw AServer_exception();
}

void	Server::game_player_leave(iprotocol::ITCP_protocol<Client> &itcp_protocol, std::string *name)
{
    delete name;
    itcp_protocol.send_result(iprotocol::Error::Packet_not_allowed);
	throw AServer_exception();
}

void	Server::game_start(iprotocol::ITCP_protocol<Client> &itcp_protocol)
{
    itcp_protocol.send_result(iprotocol::Error::Not_in_game);
	throw AServer_exception();
}

void	Server::game_ready(iprotocol::ITCP_protocol<Client> &itcp_protocol, bool)
{
    itcp_protocol.send_result(iprotocol::Error::Not_in_game);
	throw AServer_exception();
}

void    Server::game_help(iprotocol::ITCP_protocol<Client> &itcp_protocol)
{
    itcp_protocol.send_result(iprotocol::Error::Not_in_game);
    throw AServer_exception();
}

void    Server::game_hint(iprotocol::ITCP_protocol<Client> &itcp_protocol, iprotocol::Game_stone *stone)
{
    delete stone;
    itcp_protocol.send_result(iprotocol::Error::Not_in_game);
    throw AServer_exception();
}

void    Server::game_score(iprotocol::ITCP_protocol<Client> &itcp_protocol, iprotocol::Game_score *game_score)
{
    delete game_score;
    itcp_protocol.send_result(iprotocol::Error::Packet_not_allowed);
    throw AServer_exception();
}

void	Server::game_result(iprotocol::ITCP_protocol<Client> &itcp_protocol, iprotocol::Game_result *game_result)
{
    delete game_result;
    itcp_protocol.send_result(iprotocol::Error::Packet_not_allowed);
	throw AServer_exception();
}

void	Server::game_message(iprotocol::ITCP_protocol<Client> &itcp_protocol, iprotocol::Message *message)
{
    if (itcp_protocol.get_data()->get_login() == nullptr)
    {
        delete message->name;
        delete message->message;
        delete message;
        itcp_protocol.send_result(iprotocol::Error::Not_connected);
		throw AServer_exception();
    }
    if (*itcp_protocol.get_data()->get_login() == *message->name)
    {
        for (iprotocol::ITCP_protocol<Client> *it : m_itcp_protocols)
            it->send_game_message(*message);
        for (Game *game : m_games)
            for (iprotocol::ITCP_protocol<Client> *it : game->get_players())
                it->send_game_message(*message);
    }
    else
    {
        for (iprotocol::ITCP_protocol<Client> *it : m_itcp_protocols)
        {
            Client  *client = it->get_data();

            if (*message->name == *client->get_login())
            {
                it->send_game_message(*message);
                delete message->name;
                delete message->message;
                delete message;
                return;
            }
        }
        for (Game *game : m_games)
            for (iprotocol::ITCP_protocol<Client> *it : game->get_players())
            {
                Client  *client = it->get_data();

                if (*message->name == *client->get_login())
                {
                    it->send_game_message(*message);
                    break;
                }
            }
    }
    delete message->name;
    delete message->message;
    delete message;
}

AServer_exception::AServer_exception(void) noexcept
{
}

AServer_exception::AServer_exception(AServer_exception const &) noexcept
{
}

AServer_exception::~AServer_exception(void) noexcept
{
}

AServer_exception     &AServer_exception::operator=(AServer_exception const &) noexcept
{
    return (*this);
}

char const  *AServer_exception::AServer_exception::what(void) const noexcept
{
    return ("AServer_exception");
}

Server_exception_client_transfer::Server_exception_client_transfer(Game *game) noexcept :
    m_game(game)
{
}

Server_exception_client_transfer::Server_exception_client_transfer(Server_exception_client_transfer const &other) noexcept :
    AServer_exception(),
    m_game(other.m_game)
{
}

Server_exception_client_transfer::~Server_exception_client_transfer(void) noexcept
{
}

Server_exception_client_transfer     &Server_exception_client_transfer::operator=(Server_exception_client_transfer const &) noexcept
{
    return (*this);
}

char const  *Server_exception_client_transfer::Server_exception_client_transfer::what(void) const noexcept
{
    return ("Server_exception_client_transfer");
}

Server_exception_client_disconnected::Server_exception_client_disconnected(void) noexcept :
    AServer_exception()
{
}

Server_exception_client_disconnected::Server_exception_client_disconnected(Server_exception_client_disconnected const &) noexcept :
    AServer_exception()
{
}

Server_exception_client_disconnected::~Server_exception_client_disconnected(void) noexcept
{
}

Server_exception_client_disconnected     &Server_exception_client_disconnected::operator=(Server_exception_client_disconnected const &) noexcept
{
    return (*this);
}

char const  *Server_exception_client_disconnected::Server_exception_client_disconnected::what(void) const noexcept
{
    return ("Server_exception_client_disconnected");
}
