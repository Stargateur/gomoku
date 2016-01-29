//
// Server.cpp for Server in /home/plasko_a/projet/gomoku/source
//
// Made by Antoine Plaskowski
// Login   <antoine.plaskowski@epitech.eu>
//
// Started on  Tue Jan 26 17:50:03 2016 Antoine Plaskowski
// Last update Thu Jan 28 13:05:34 2016 Antoine Plaskowski
//

#include	"TCP_protocol.hpp"
#include	"TCP_server.hpp"
#include	"TCP_client.hpp"
#include	"Standard.hpp"
#include	"Server.hpp"
#include	"Time.hpp"
#include    "Time_Windows.hpp"

Server::Server(void) :
    Server(new Standard(IStandard::In))
{
            std::cerr << "lol1" << std::endl;
}

Server::Server(IStandard *istandard) try :
    Server(istandard, new TCP_server("4242"))
{
            std::cerr << "lol2" << std::endl;
}
catch (...)
{
    delete istandard;
}

Server::Server(IStandard *istandard, ITCP_server *itcp_server) try :
    Server(istandard, itcp_server, new Select())
{
        std::cerr << "lol3" << std::endl;
}
catch (...)
{
    delete itcp_server;
}

Server::Server(IStandard *istandard, ITCP_server *itcp_server, ISelect *iselect) try :
    m_istandard(istandard),
    m_itcp_server(itcp_server),
    m_iselect(iselect),
    m_timeout(new Time(5))
{
        std::cerr << "lol4" << std::endl;
}
catch (...)
{
    delete iselect;
}

Server::~Server(void)
{
    delete m_itcp_server;
    delete m_istandard;
    for (auto itcp_protocol : m_itcp_protocols)
        delete itcp_protocol;
    for (auto game : m_games)
        delete game;
    delete m_iselect;
    delete m_timeout;
}

void	Server::run(void)
{
    bool  g_keep_running = true;

    while (g_keep_running == true)
    {
        m_iselect->reset();
#ifndef	_WIN32
        m_iselect->want_read(*m_istandard);
#endif
        m_iselect->want_read(*m_itcp_server);
        for (auto itcp_protocol : m_itcp_protocols)
        {
            Client &client = *itcp_protocol->get_data();

            if (itcp_protocol->want_recv())
                m_iselect->want_read(*client.get_itcp_client());

            if (itcp_protocol->want_send())
                m_iselect->want_write(*client.get_itcp_client());
        }
        for (auto game : m_games)
        {
            for (auto *itcp_protocol : game->m_itcp_protocols)
            {
                Client &client = *itcp_protocol->get_data();

                if (itcp_protocol->want_recv())
                    m_iselect->want_read(*client.get_itcp_client());

                if (itcp_protocol->want_send())
                    m_iselect->want_write(*client.get_itcp_client());
            }
        }

        m_iselect->select();


#ifndef	_WIN32
        if (m_iselect->can_read(*m_istandard))
        {
            m_iselect->reset_read(*m_istandard);
            uint8_t       buffer[42];

            if (m_istandard->read(buffer[0], 42) == 0)
                g_keep_running = false;
        }
#endif

        if (m_iselect->can_read(*m_itcp_server))
        {
            m_iselect->reset_read(*m_itcp_server);
            Client	*client = new Client(&m_itcp_server->accept(), nullptr, new Time(), false);
#ifdef DEBUG
            std::cerr << "Un client s'est connecter" << std::endl;
#endif
            m_itcp_protocols.push_back(new TCP_protocol<Client>(this, client));
        }
        for (auto it = m_itcp_protocols.begin(); it != m_itcp_protocols.end();)
        {
            auto itcp_protocol = *it;
            Client &client = *itcp_protocol->get_data();

            try
            {
                if (m_iselect->can_read(*client.get_itcp_client()))
                {
                    m_iselect->reset_read(*client.get_itcp_client());
                    itcp_protocol->recv(*client.get_itcp_client());
                }
                else
                    timeout(*itcp_protocol);

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
                e.m_game->m_itcp_protocols.push_back(itcp_protocol);
                itcp_protocol->set_callback(e.m_game);
            }
            catch (std::exception &e)
            {
                std::cerr << e.what() << std::endl;
                delete itcp_protocol;
                it = m_itcp_protocols.erase(it);
            }
        }
        for (auto game : m_games)
        {
            auto &itcp_protocols = game->m_itcp_protocols;
            for (auto it = itcp_protocols.begin(); it != itcp_protocols.end();)
            {
                auto itcp_protocol = *it;
                Client &client = *itcp_protocol->get_data();

                try
                {
                    std::cout << client.get_login() << std::endl;
                    if (m_iselect->can_read(*client.get_itcp_client()))
                    {
                        m_iselect->reset_read(*client.get_itcp_client());
                        itcp_protocol->recv(*client.get_itcp_client());
                    }
                    else
                        timeout(*itcp_protocol);

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
                    itcp_protocol->set_callback(this);
                    m_itcp_protocols.push_back(itcp_protocol);
                }
                catch (std::exception &e)
                {
                    std::cerr << e.what() << std::endl;
                    delete itcp_protocol;
                    it = itcp_protocols.erase(it);
                }
            }
        }
    }
}

void	Server::timeout(ITCP_protocol<Client> &itcp_protocol) const
{
    Client	&client = *itcp_protocol.get_data();
    ITime		&last = *client.get_last();
    intmax_t      second = last.get_second();
    intmax_t      nano = last.get_nano();

    last.now();
    if (last.get_second() - second > m_timeout->get_second()
        || (last.get_second() - second == m_timeout->get_second()
            && last.get_nano() - nano > m_timeout->get_nano()))
    {
        if (client.get_wait_pong() == true)
            throw std::logic_error("timeout");
        client.set_wait_pong(true);
        itcp_protocol.send_ping();
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
    if (*login != *password)
        throw std::logic_error("Wrong login() and/or password");
    itcp_protocol.get_data()->set_login(login);
    delete password;
}

void	Server::disconnect(ITCP_protocol<Client> &itcp_protocol)
{
    throw Server_exception_client_disconnected();
}

void	Server::ping(ITCP_protocol<Client> &itcp_protocol)
{
    itcp_protocol.send_pong();
}

void	Server::pong(ITCP_protocol<Client> &itcp_protocol)
{
    Client	&client = *itcp_protocol.get_data();

    client.set_wait_pong(false);
}

void	Server::create_game(ITCP_protocol<Client> &itcp_protocol, typename ITCP_protocol<Client>::Game *game_info)
{
    Game	*game = new Game(*this, game_info->name);

    m_games.push_back(game);
    delete game_info->owner;
    delete game_info;
    throw Server_exception_client_transfer(game);
}

void	Server::join_game(ITCP_protocol<Client> &itcp_protocol, typename ITCP_protocol<Client>::Game *game_info)
{
    for (auto game : m_games)
        if (*game_info->name == game->get_name())
            throw Server_exception_client_transfer(game);
    throw AServer_exception();
}

void	Server::leave_game(ITCP_protocol<Client> &itcp_protocol)
{
    throw AServer_exception();
}

void	Server::put_stone_game(ITCP_protocol<Client> &itcp_protocol, typename ITCP_protocol<Client>::Game_stone *stone)
{
    throw AServer_exception();
}

void	Server::change_param_game(ITCP_protocol<Client> &itcp_protocol, typename ITCP_protocol<Client>::Game_param *param)
{
    throw AServer_exception();
}

void	Server::list_param_game(ITCP_protocol<Client> &itcp_protocol, std::list<typename ITCP_protocol<Client>::Game_param *> *params)
{
    throw AServer_exception();
}

void	Server::game_created(ITCP_protocol<Client> &itcp_protocol, typename ITCP_protocol<Client>::Game *game)
{
    throw AServer_exception();
}

void	Server::game_player_joined(ITCP_protocol<Client> &itcp_protocol, std::string *name)
{
    throw AServer_exception();
}

void	Server::game_player_left(ITCP_protocol<Client> &itcp_protocol, std::string *name)
{
    throw AServer_exception();
}

void	Server::game_param_changed(ITCP_protocol<Client> &itcp_protocol, typename ITCP_protocol<Client>::Game_param *param)
{
    throw AServer_exception();
}

void	Server::game_stone_put(ITCP_protocol<Client> &itcp_protocol, typename ITCP_protocol<Client>::Game_stone *stone)
{
    throw AServer_exception();
}

void	Server::game_deleted(ITCP_protocol<Client> &itcp_protocol, typename ITCP_protocol<Client>::Game *game)
{
    throw AServer_exception();
}

void	Server::start_game(ITCP_protocol<Client> &itcp_protocol)
{
    throw AServer_exception();
}

void	Server::ready_game(ITCP_protocol<Client> &itcp_protocol, bool ready)
{
    throw AServer_exception();
}

void	Server::result_game(ITCP_protocol<Client> &itcp_protocol, typename ITCP_protocol<Client>::Game_result *game_result)
{
    throw AServer_exception();
}

void	Server::message(ITCP_protocol<Client> &itcp_protocol, typename ITCP_protocol<Client>::Message *message)
{
    if (*itcp_protocol.get_data()->get_login() == *message->name)
        for (auto it : m_itcp_protocols)
            it->send_message(*message);
    else
    {
        for (auto it : m_itcp_protocols)
        {
            Client  *client = it->get_data();

            if (*message->name == *client->get_login())
            {
                it->send_message(*message);
                return;
            }
        }
        for (auto game : m_games)
            for (auto it : game->m_itcp_protocols)
            {
                Client  *client = it->get_data();

                if (*message->name == *client->get_login())
                {
                    it->send_message(*message);
                    return;
                }
            }
    }
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
