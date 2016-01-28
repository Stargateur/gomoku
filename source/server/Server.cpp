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

Server::Server(void) :
    m_itcp_server(new TCP_server("4242")),
    m_istandard(new Standard(IStandard::In)),
    m_itcp_protocols(),
    m_iselect(new Select()),
    m_timeout(new Time(5))
{
}

Server::~Server(void)
{
    delete m_itcp_server;
    delete m_istandard;
    for (auto itcp_protocol : m_itcp_protocols)
        delete itcp_protocol;
    delete m_iselect;
    delete m_timeout;
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
                m_iselect->want_read(*client.itcp_client);

            if (itcp_protocol->want_send())
                m_iselect->want_write(*client.itcp_client);
        }

        m_iselect->select();

        if (m_iselect->can_read(*m_istandard))
        {
            uint8_t       buffer[42];

            if (m_istandard->read(buffer[0], 42) == 0)
                g_keep_running = false;
        }

        if (m_iselect->can_read(*m_itcp_server))
        {
            Client	*client = new Client;
            client->itcp_client = &m_itcp_server->accept();
            client->last = new Time();
            m_itcp_protocols.push_back(new TCP_protocol<Client>(this, client));
        }
        for (auto it = m_itcp_protocols.begin(); it != m_itcp_protocols.end();)
        {
            auto itcp_protocol = *it;
            Client &client = *itcp_protocol->get_data();

            try
            {
                if (m_iselect->can_read(*client.itcp_client))
                    itcp_protocol->recv(*client.itcp_client);
                else
                    timeout(*itcp_protocol);

                if (m_iselect->can_write(*client.itcp_client))
                    itcp_protocol->send(*client.itcp_client);

                it++;
            }
            catch (...)
            {
                delete itcp_protocol->get_data();
                delete itcp_protocol;
                it = m_itcp_protocols.erase(it);
            }
        }
    }
}

void	Server::timeout(ITCP_protocol<Client> &itcp_protocol) const
{
    Client	&client = *itcp_protocol.get_data();
    ITime		&last = *client.last;
    intmax_t      second = last.get_second();
    intmax_t      nano = last.get_nano();

    last.now();
    if (last.get_second() - second > m_timeout->get_second()
            || (last.get_second() - second == m_timeout->get_second()
                && last.get_nano() - nano > m_timeout->get_nano()))
    {
        if (client.wait_pong == true)
            throw std::logic_error("timeout");
        client.wait_pong = true;
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
    std::cout << *login << " " << *password << std::endl;
    if (*login != *password)
        throw std::logic_error("Wrong login and/or password");
    delete itcp_protocol.get_data()->login;
    itcp_protocol.get_data()->login = login;
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
    Client	&client = *itcp_protocol.get_data();

    client.wait_pong = false;
}

void	Server::create_game(ITCP_protocol<Client> &itcp_protocol, typename ITCP_protocol<Client>::Game *game_info)
{
    Game	*game = new Game(*this, game_info->name);

    itcp_protocol.set_callback(game);
    game->m_itcp_protocols.push_back(&itcp_protocol);
    m_games.push_back(game);
    throw std::logic_error("don't sup this player");
}

void	Server::join_game(ITCP_protocol<Client> &itcp_protocol, typename ITCP_protocol<Client>::Game *game_info)
{
    for (auto game : m_games)
    {
        if (*game_info->name == game->get_name())
        {
        }
    }
}

void	Server::leave_game(ITCP_protocol<Client> &itcp_protocol)
{
    throw std::logic_error("tu n'est pas en game");
}

void	Server::put_stone_game(ITCP_protocol<Client> &itcp_protocol, typename ITCP_protocol<Client>::Game_stone *stone)
{
    throw std::logic_error("tu n'est pas en game");
}

void	Server::change_param_game(ITCP_protocol<Client> &itcp_protocol, typename ITCP_protocol<Client>::Game_param *param)
{
    throw std::logic_error("tu n'est pas en game");
}

void	Server::list_param_game(ITCP_protocol<Client> &itcp_protocol, std::list<typename ITCP_protocol<Client>::Game_param *> *params)
{
    throw std::logic_error("tu n'est pas en game");
}

void	Server::game_created(ITCP_protocol<Client> &itcp_protocol, typename ITCP_protocol<Client>::Game *game)
{
    throw std::logic_error("je suis le server et toi le client !");
}

void	Server::game_player_joined(ITCP_protocol<Client> &itcp_protocol, std::string *name)
{
    throw std::logic_error("je suis le server et toi le client !");
}

void	Server::game_player_left(ITCP_protocol<Client> &itcp_protocol, std::string *name)
{
    throw std::logic_error("je suis le server et toi le client !");
}

void	Server::game_param_changed(ITCP_protocol<Client> &itcp_protocol, typename ITCP_protocol<Client>::Game_param *param)
{
    throw std::logic_error("je suis le server et toi le client !");
}

void	Server::game_stone_put(ITCP_protocol<Client> &itcp_protocol, typename ITCP_protocol<Client>::Game_stone *stone)
{
    throw std::logic_error("je suis le server et toi le client !");
}

void	Server::game_deleted(ITCP_protocol<Client> &itcp_protocol, typename ITCP_protocol<Client>::Game *game)
{
    throw std::logic_error("je suis le server et toi le client !");
}

void	Server::start_game(ITCP_protocol<Client> &itcp_protocol)
{
    throw std::logic_error("tu n'est pas en game");
}

void	Server::ready_game(ITCP_protocol<Client> &itcp_protocol, bool ready)
{
    throw std::logic_error("tu n'est pas en game");
}

void	Server::result_game(ITCP_protocol<Client> &itcp_protocol, typename ITCP_protocol<Client>::Game_result *game_result)
{
    throw std::logic_error("je suis le server et toi le client !");
}

void	Server::message(ITCP_protocol<Client> &itcp_protocol, typename ITCP_protocol<Client>::Message *message)
{
    if (*itcp_protocol.get_data()->login == *message->name)
        for (auto it : m_itcp_protocols)
            it->send_message(*message);
    else
        for (auto it : m_itcp_protocols)
        {
            Client	*client = it->get_data();

            if (*message->name == *client->login)
            {
                it->send_message(*message);
                break;
            }
        }
}

IServer_exception::IServer_exception(void) noexcept
{
}

IServer_exception::IServer_exception(IServer_exception const &) noexcept
{
}

IServer_exception::~IServer_exception(void) noexcept
{
}

IServer_exception     &IServer_exception::operator=(IServer_exception const &) noexcept
{
    return (*this);
}

Server_exception_client_transfer::Server_exception_client_transfer(Game &game) noexcept :
m_game(game)
{
}

Server_exception_client_transfer::Server_exception_client_transfer(Server_exception_client_transfer const &other) noexcept :
IServer_exception(),
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
