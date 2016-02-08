//
// Server.cpp for Server in /home/plasko_a/projet/gomoku/source
//
// Made by Antoine Plaskowski
// Login   <antoine.plaskowski@epitech.eu>
//
// Started on  Tue Jan 26 17:50:03 2016 Antoine Plaskowski
// Last update Fri Jan 29 23:56:37 2016 Antoine Plaskowski
//

#include    <thread>
#include	"TCP_protocol.hpp"
#include	"TCP_server.hpp"
#include	"TCP_client.hpp"
#include	"Server.hpp"
#include	"Time.hpp"
#include    "Utils.hpp"

Server::Server(void) try :
    Server(new TCP_server("4242"))
{
}
catch (...)
{
}

Server::Server(ITCP_server *itcp_server) try :
    Server(itcp_server, new Select())
{
}
catch (...)
{
    delete itcp_server;
}

Server::Server(ITCP_server *itcp_server, ISelect *iselect) try :
    m_itcp_server(itcp_server),
    m_iselect(iselect),
    m_timeout(new Time(5))
{
}
catch (...)
{
    delete iselect;
}

Server::~Server(void)
{
    delete m_itcp_server;
    for (auto itcp_protocol : m_itcp_protocols)
        delete itcp_protocol;
    for (auto game : m_games)
        delete game;
    delete m_iselect;
    delete m_timeout;
}

void    Server::pre_run(void) const
{
    m_iselect->reset();

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
        game->pre_run(*m_iselect);
    }
}

void	Server::run(void)
{
    m_iselect->select();

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
                itcp_protocol->get_data()->get_last()->now();
                m_iselect->reset_read(*client.get_itcp_client());
                itcp_protocol->recv(*client.get_itcp_client());
            }
            else
                Utils::timeout(*itcp_protocol, *m_timeout);

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
        catch (std::exception &e)
        {
            std::cerr << e.what() << std::endl;
            delete itcp_protocol;
            it = m_itcp_protocols.erase(it);
        }
    }
    auto it_game = m_games.begin();
    while (it_game != m_games.end())
    {
        auto game = *it_game;
        try
        {
            Time lol;
            game->run(*m_iselect, lol);
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
            it_game = m_games.erase(it_game);
            std::cerr << e.what() << std::endl;
            for (auto itcp_protocol : m_itcp_protocols)
                game->send_game_deleted(*itcp_protocol);
            delete game;
            for (auto game_it : m_games)
                for (auto game_player_it : game_it->get_players())
                    game_it->send_game_deleted(*game_player_it);
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
    {
        delete login;
        delete password;
        throw std::logic_error("Wrong version");
    }
    if (*login != *password)
    {
        delete login;
        delete password;
        throw std::logic_error("Wrong login() and/or password");
    }
    for (auto itcp_protocol : m_itcp_protocols)
    {
        auto client = itcp_protocol->get_data();

        if (client->get_login() != nullptr)
            if (*client->get_login() == *login)
            {
                delete login;
                delete password;
                throw std::logic_error("this login is already used");
            }
    }
    itcp_protocol.get_data()->set_login(login);
    for (auto game : m_games)
        game->send_game_created(itcp_protocol);
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
    auto client = itcp_protocol.get_data();
    if (client->get_login() == nullptr)
    {
        delete game_info->name;
        delete game_info;
        throw AServer_exception();
    }
    for (auto game_it : m_games)
        if (game_it->get_name() == *game_info->name)
            {
                delete game_info->name;
                delete game_info;
                throw AServer_exception();
            }
    Game	*game = new Game(*this, game_info->name);

    delete game_info;
    for (auto it : m_itcp_protocols)
        game->send_game_created(*it);        
    for (auto it_game : m_games)
        for (auto it : it_game->get_players())
            game->send_game_created(*it);
    m_games.push_back(game);
    throw Server_exception_client_transfer(game);
}

void	Server::join_game(ITCP_protocol<Client> &itcp_protocol, typename ITCP_protocol<Client>::Game *game_info)
{
    auto client = itcp_protocol.get_data();
    if (client->get_login() == nullptr)
    {
        delete game_info->name;
        delete game_info;
        throw AServer_exception();
    }
    for (auto game : m_games)
        if (*game_info->name == game->get_name())
        {
            delete game_info->name;
            delete game_info;
            throw Server_exception_client_transfer(game);
        }
    delete game_info->name;
    delete game_info;
    throw AServer_exception();
}

void	Server::leave_game(ITCP_protocol<Client> &itcp_protocol)
{
    throw AServer_exception();
}

void	Server::put_stone_game(ITCP_protocol<Client> &itcp_protocol, typename ITCP_protocol<Client>::Game_stone *stone)
{
    delete stone;
    throw AServer_exception();
}

void	Server::change_param_game(ITCP_protocol<Client> &itcp_protocol, typename ITCP_protocol<Client>::Game_param *param)
{
    delete param;
    throw AServer_exception();
}

void    Server::change_param_player_game(ITCP_protocol<Client> &itcp_protocol, typename ITCP_protocol<Client>::Game_player_param *param)
{
    delete param;
    throw AServer_exception();
}

void    Server::list_param_player_game(ITCP_protocol<Client> &itcp_protocol, std::list<typename ITCP_protocol<Client>::Game_player_param *> *params)
{
    for (auto param : *params)
    {
        delete param->name;
        delete param->value;
        delete param;
    }
    delete params;
    throw AServer_exception();
}

void    Server::list_param_game(ITCP_protocol<Client> &itcp_protocol, std::list<typename ITCP_protocol<Client>::Game_param *> *params)
{
    for (auto param : *params)
    {
        delete param->name;
        delete param->value;
        delete param;
    }
    delete params;
    throw AServer_exception();
}

void	Server::game_created(ITCP_protocol<Client> &itcp_protocol, typename ITCP_protocol<Client>::Game *game)
{
    delete game->name;
    delete game;
    throw AServer_exception();
}

void	Server::game_player_joined(ITCP_protocol<Client> &itcp_protocol, std::string *name)
{
    delete name;
    throw AServer_exception();
}

void	Server::game_player_left(ITCP_protocol<Client> &itcp_protocol, std::string *name)
{
    delete name;
    throw AServer_exception();
}

void    Server::game_player_param_changed(ITCP_protocol<Client> &itcp_protocol, typename ITCP_protocol<Client>::Game_player_param *param)
{
    delete param->name;
    delete param->value;
    delete param;
    throw AServer_exception();
}

void	Server::game_param_changed(ITCP_protocol<Client> &itcp_protocol, typename ITCP_protocol<Client>::Game_param *param)
{
    delete param->name;
    delete param->value;
    delete param;
    throw AServer_exception();
}

void	Server::game_stone_put(ITCP_protocol<Client> &itcp_protocol, typename ITCP_protocol<Client>::Game_stone *stone)
{
    delete stone;
    throw AServer_exception();
}

void	Server::game_deleted(ITCP_protocol<Client> &itcp_protocol, typename ITCP_protocol<Client>::Game *game)
{
    delete game->name;
    delete game;
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
    delete game_result->winner;
    delete game_result;
    throw AServer_exception();
}

void	Server::message(ITCP_protocol<Client> &itcp_protocol, typename ITCP_protocol<Client>::Message *message)
{
    auto client = itcp_protocol.get_data();
    if (client->get_login() == nullptr)
    {
        delete message->name;
        delete message->message;
        delete message;
        throw AServer_exception();
    }
    if (*itcp_protocol.get_data()->get_login() == *message->name)
    {
        for (auto it : m_itcp_protocols)
            it->send_message(*message);
        for (auto game : m_games)
            for (auto it : game->get_players())
                it->send_message(*message);
    }
    else
    {
        for (auto it : m_itcp_protocols)
        {
            Client  *client = it->get_data();

            if (*message->name == *client->get_login())
            {
                it->send_message(*message);
                delete message->name;
                delete message->message;
                delete message;
                return;
            }
        }
        for (auto game : m_games)
            for (auto it : game->get_players())
            {
                Client  *client = it->get_data();

                if (*message->name == *client->get_login())
                {
                    it->send_message(*message);
                    delete message->name;
                    delete message->message;
                    delete message;
                    return;
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
