#include    <iostream>
#include    "Game.hpp"
#include    "Utils.hpp"

Game::Game(typename iprotocol::ITCP_protocol<Client>::Callback &callback, std::string *name) :
    ACallback(callback),
    m_is_start(false),
    m_name(name),
    m_arbitre(*this),
    m_black(m_arbitre),
    m_white(m_arbitre),
    m_timeout(5)
{
    iprotocol::Game_player_param *game_player_param = new iprotocol::Game_player_param;

    game_player_param->name = new std::string("color");
    game_player_param->value = new std::string();
    m_param_player.push_back(game_player_param);
    iprotocol::Game_param *game_param = new iprotocol::Game_param;

    game_param->name = new std::string("double trois");
    game_param->value = new std::string("true");
    m_params.push_back(game_param);
    game_param = new iprotocol::Game_param;
    game_param->name = new std::string("cinq cassable");
    game_param->value = new std::string("true");
    game_param = new iprotocol::Game_param;
    game_param->name = new std::string("seulement cinq");
    game_param->value = new std::string("false");
    m_params.push_back(game_param);
    game_param = new iprotocol::Game_param;
    game_param->name = new std::string("ia");
    game_param->value = new std::string();
}

Game::~Game(void)
{
    for (iprotocol::Game_param *game_param : m_params)
    {
        delete game_param->name;
        delete game_param->value;
        delete game_param;
    }
    for (iprotocol::Game_player_param *game_player_param : m_param_player)
    {
        delete game_player_param->name;
        delete game_player_param->value;
        delete game_player_param;
    }
    delete m_name;
}

void    Game::pre_run(ISelect &iselect)
{
    for (iprotocol::ITCP_protocol<Client> *itcp_protocol : m_itcp_protocols)
    {
        Client &client = *itcp_protocol->get_data();

        if (itcp_protocol->want_recv())
            iselect.want_read(*client.get_itcp_client());

        if (itcp_protocol->want_send())
            iselect.want_write(*client.get_itcp_client());
    }

	auto disconnect = m_disconnecteds.begin();
	while (disconnect != m_disconnecteds.end())
	{
		iprotocol::ITCP_protocol<Client> *itcp_protocol = *disconnect;
		Client &client = *itcp_protocol->get_data();

		if (itcp_protocol->want_send())
		{
			iselect.want_write(*client.get_itcp_client());
			disconnect++;
		}
		else
		{
			disconnect = m_disconnecteds.erase(disconnect);
			delete itcp_protocol;
            #ifndef NDEBUG
            std::cerr << "GAME : DELETE CLIENT" << std::endl;
            #endif
		}
	}
}

void    Game::run(ISelect &iselect)
{
    if (m_itcp_protocols.size() == 0 && m_disconnecteds.size() == 0)
        throw AGame_exception();
    auto disconnect = m_disconnecteds.begin();
    while (disconnect != m_disconnecteds.end())
    {
        iprotocol::ITCP_protocol<Client> *itcp_protocol = *disconnect;
        Client &client = *itcp_protocol->get_data();
        try
        {
            if (iselect.can_write(*client.get_itcp_client()))
            {
                iselect.reset_write(*client.get_itcp_client());
                itcp_protocol->send(*client.get_itcp_client());
            }
            else
                throw AGame_exception();
            disconnect++;
        }
        catch (std::exception &e)
        {
            std::cerr << e.what() << std::endl;
            disconnect = m_disconnecteds.erase(disconnect);
            delete itcp_protocol;
            #ifndef NDEBUG
            std::cerr << "GAME : DELETE CLIENT" << std::endl;
            #endif
        }
    }
    auto it = m_itcp_protocols.begin();
    while (it != m_itcp_protocols.end())
    {
        iprotocol::ITCP_protocol<Client> *itcp_protocol = *it;
        Client &client = *itcp_protocol->get_data();

        try
        {
            if (iselect.can_read(*client.get_itcp_client()))
            {
                itcp_protocol->get_data()->get_last() = std::chrono::steady_clock::now();
                iselect.reset_read(*client.get_itcp_client());
                itcp_protocol->recv(*client.get_itcp_client());
            }
            else
                Utils::timeout(*itcp_protocol, m_timeout);

            if (iselect.can_write(*client.get_itcp_client()))
            {
                iselect.reset_write(*client.get_itcp_client());
                itcp_protocol->send(*client.get_itcp_client());
            }
            it++;
        }
        catch (Game_exception_client_transfer &e)
        {
            e.m_client = itcp_protocol;
            delete_player(it);
            throw;
        }
        catch (AGame_exception &e)
        {
            std::cerr << e.what() << std::endl;
            delete_player(it);
            m_disconnecteds.push_back(itcp_protocol);
        }
        catch (std::exception &e)
        {
            std::cerr << e.what() << std::endl;
            delete_player(it);
            delete itcp_protocol;
        }
    }
}

void    Game::add_player(iprotocol::ITCP_protocol<Client> *player)
{
    for (iprotocol::ITCP_protocol<Client> *itcp_protocol : m_itcp_protocols)
        itcp_protocol->send_game_player_joined(*player->get_data()->get_login());
    player->set_callback(this);
    player->send_list_param_game(m_params);
    player->send_list_param_player_game(m_param_player);
    m_arbitre.Welcome(*player);
    m_itcp_protocols.push_back(player);
}

void    Game::delete_player(std::list<iprotocol::ITCP_protocol<Client> *>::iterator &it)
{
    Client  *client = (*it)->get_data();
    it = m_itcp_protocols.erase(it);
    for (iprotocol::ITCP_protocol<Client> *itcp_protocol : m_itcp_protocols)
        itcp_protocol->send_game_player_left(*client->get_login());
}

std::list<iprotocol::ITCP_protocol<Client> *> const   &Game::get_players(void) const
{
    return (m_itcp_protocols);
}

std::list<iprotocol::ITCP_protocol<Client> *>   &Game::get_players(void)
{
    return (m_itcp_protocols);
}

std::string const	&Game::get_name(void) const
{
    return (*m_name);
}

void    Game::send_game_created(iprotocol::ITCP_protocol<Client> &itcp_protocol) const
{
    iprotocol::Game info;
    info.name = m_name;
    itcp_protocol.send_game_created(info);
}

void    Game::send_game_deleted(iprotocol::ITCP_protocol<Client> &itcp_protocol) const
{
    iprotocol::Game info;
    info.name = m_name;
    itcp_protocol.send_game_deleted(info);
}

void	Game::create_game(iprotocol::ITCP_protocol<Client> &itcp_protocol, iprotocol::Game *game)
{
    delete game->name;
    delete game;
    itcp_protocol.send_result(iprotocol::Error::Already_in_game);
    throw AGame_exception();
}

void	Game::join_game(iprotocol::ITCP_protocol<Client> &itcp_protocol, iprotocol::Game *game)
{
    delete game->name;
    delete game;
    itcp_protocol.send_result(iprotocol::Error::Already_in_game);
    throw AGame_exception();
}

void	Game::leave_game(iprotocol::ITCP_protocol<Client> &)
{
    throw Game_exception_client_transfer(nullptr);
}

void	Game::put_stone_game(iprotocol::ITCP_protocol<Client> &itcp_protocol, iprotocol::Game_stone *stone)
{
	if (itcp_protocol.get_callback() != &m_white && itcp_protocol.get_callback() != &m_black)
	{
        itcp_protocol.send_result(iprotocol::Error::Packet_not_allowed);
        delete stone;
		throw AGame_exception();
	}
	for (iprotocol::ITCP_protocol<Client> *it : m_itcp_protocols)
		it->send_game_stone_put(*stone);
}

void    Game::change_param_player_game(iprotocol::ITCP_protocol<Client> &itcp_protocol, iprotocol::Game_player_param *param)
{
    if (*param->name == "color")
    {
        if (*param->value == "white")
            itcp_protocol.set_callback(&m_white);
        else if (*param->value == "black")
            itcp_protocol.set_callback(&m_black);
    }
    else
        itcp_protocol.send_result(iprotocol::Error::Game_player_param_not_exist);
    delete param->name;
    delete param->value;
    delete param;
}

void    Game::change_param_game(iprotocol::ITCP_protocol<Client> &itcp_protocol, iprotocol::Game_param *param)
{
    delete param->value;
    delete param->name;
    delete param;
    itcp_protocol.send_result(iprotocol::Error::Game_param_not_exist);
    throw AGame_exception();
}

void	Game::start_game(iprotocol::ITCP_protocol<Client> &itcp_protocol)
{
    if (m_white.is_ready() == false || m_black.is_ready() == false)
        itcp_protocol.send_result(iprotocol::Error::All_player_are_not_ready);
    else
        m_is_start = true;
}

void	Game::ready_game(iprotocol::ITCP_protocol<Client> &itcp_protocol, bool)
{
    itcp_protocol.send_result(iprotocol::Error::Packet_not_allowed);
    throw AGame_exception();
}

void    Game::result_game(iprotocol::ITCP_protocol<Client> &itcp_protocol, iprotocol::Game_result *game_result)
{
    if (itcp_protocol.get_callback() != &m_white && itcp_protocol.get_callback() != &m_black)
    {
        itcp_protocol.send_result(iprotocol::Error::Packet_not_allowed);
        delete game_result->winner;
        delete game_result;
        throw AGame_exception();
    }
    for (iprotocol::ITCP_protocol<Client> *it : m_itcp_protocols)
        it->send_result_game(*game_result);
//    throw AGame_exception();
}

AGame_exception::AGame_exception(void) noexcept
{
}

AGame_exception::AGame_exception(AGame_exception const &) noexcept
{
}

AGame_exception::~AGame_exception(void) noexcept
{
}

AGame_exception     &AGame_exception::operator=(AGame_exception const &) noexcept
{
    return (*this);
}

char const  *AGame_exception::AGame_exception::what(void) const noexcept
{
    return ("AGame_exception");
}

Game_exception_client_transfer::Game_exception_client_transfer(iprotocol::ITCP_protocol<Client> *client) noexcept :
    m_client(client)
{
}

Game_exception_client_transfer::Game_exception_client_transfer(Game_exception_client_transfer const &other) noexcept :
    AGame_exception(),
    m_client(other.m_client)
{
}

Game_exception_client_transfer::~Game_exception_client_transfer(void) noexcept
{
}

Game_exception_client_transfer     &Game_exception_client_transfer::operator=(Game_exception_client_transfer const &) noexcept
{
    return (*this);
}

char const  *Game_exception_client_transfer::Game_exception_client_transfer::what(void) const noexcept
{
    return ("Game_exception_client_transfer");
}
