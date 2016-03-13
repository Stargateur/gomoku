#include    <iostream>
#include    "Game.hpp"
#include    "Utils.hpp"
#include    "AI.hpp"

Game::Game(typename iprotocol::ITCP_protocol<Client>::Callback &callback, std::string *name) :
    ACallback(callback),
    m_is_start(false),
    m_name(name),
    m_board(),
    m_arbitre(),
    m_black(*this),
    m_white(*this),
    m_timeout(5)
{
}

Game::~Game(void)
{
	for (iprotocol::ITCP_protocol<Client> *client : m_itcp_protocols)
		delete client;
	for (iprotocol::ITCP_protocol<Client> *client : m_disconnecteds)
		delete client;
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
	if (m_itcp_protocols.size() == 0 && m_disconnecteds.size() == 0)
		throw AGame_exception();
}

void    Game::add_player(iprotocol::ITCP_protocol<Client> *player)
{
    for (iprotocol::ITCP_protocol<Client> *itcp_protocol : m_itcp_protocols)
        itcp_protocol->send_game_player_join(*player->get_data()->get_login());
    player->set_callback(this);
    m_itcp_protocols.push_back(player);
    iprotocol::Game game;
    game.name = m_name;
    player->send_game_join(game);
}

void    Game::delete_player(std::list<iprotocol::ITCP_protocol<Client> *>::iterator &it)
{
    Client  *client = (*it)->get_data();
    it = m_itcp_protocols.erase(it);
    for (iprotocol::ITCP_protocol<Client> *itcp_protocol : m_itcp_protocols)
        itcp_protocol->send_game_player_leave(*client->get_login());
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

void    Game::send_game_create(iprotocol::ITCP_protocol<Client> &itcp_protocol) const
{
    iprotocol::Game info;
    info.name = m_name;
    itcp_protocol.send_game_create(info);
}

void    Game::send_game_delete(iprotocol::ITCP_protocol<Client> &itcp_protocol) const
{
    iprotocol::Game info;
    info.name = m_name;
    itcp_protocol.send_game_delete(info);
}

void	Game::game_create(iprotocol::ITCP_protocol<Client> &itcp_protocol, iprotocol::Game *game)
{
    delete game->name;
    delete game;
    itcp_protocol.send_result(iprotocol::Error::Already_in_game);
    throw AGame_exception();
}

void	Game::game_join(iprotocol::ITCP_protocol<Client> &itcp_protocol, iprotocol::Game *game)
{
    delete game->name;
    delete game;
    itcp_protocol.send_result(iprotocol::Error::Already_in_game);
    throw AGame_exception();
}

void	Game::game_leave(iprotocol::ITCP_protocol<Client> &)
{
    throw Game_exception_client_transfer(nullptr);
}

void	Game::game_stone_put(iprotocol::ITCP_protocol<Client> &itcp_protocol, iprotocol::Game_stone *stone)
{
    if (itcp_protocol.get_callback() != &m_white && itcp_protocol.get_callback() != &m_black)
    {
        itcp_protocol.send_result(iprotocol::Error::Packet_not_allowed);
        throw AGame_exception();
    }
    else
    {
        if (Arbitre::can_put_stone(stone, m_board, false))
        {
            std::vector<iprotocol::Game_stone *>    stones;
            m_board.put_stone(stone->x, stone->y, stone->color, stones);
            for (iprotocol::Game_stone *sto : stones)
            {
                for (iprotocol::ITCP_protocol<Client> *client : m_itcp_protocols)
                    client->send_game_stone_put(*sto);
                delete sto;
            }
			Square::col	col;
			if ((col = Arbitre::check_victory(m_board, false, true)) != Square::col::None)
			{
				iprotocol::Game_result	result;
				result.winner = col == Square::col::Black ? iprotocol::Game_result::Black : iprotocol::Game_result::White;
				for (iprotocol::ITCP_protocol<Client> *client : m_itcp_protocols)
					client->send_game_result(result);
			}
			else
			{
				iprotocol::Game_stone	ai;
				AI::play(m_board, ai, 1);
				if (Arbitre::can_put_stone(&ai, m_board, false))
				{
					std::vector<iprotocol::Game_stone *>    stones;
					m_board.put_stone(ai.x, ai.y, ai.color, stones);
					for (iprotocol::Game_stone *sto : stones)
					{
						for (iprotocol::ITCP_protocol<Client> *client : m_itcp_protocols)
							client->send_game_stone_put(*sto);
						delete sto;
					}
					Square::col	col;
					if ((col = Arbitre::check_victory(m_board, false, true)) != Square::col::None)
					{
						iprotocol::Game_result	result;
						result.winner = col == Square::col::Black ? iprotocol::Game_result::Black : iprotocol::Game_result::White;
						for (iprotocol::ITCP_protocol<Client> *client : m_itcp_protocols)
							client->send_game_result(result);
					}
				}
			}
        }
    }
    delete stone;
}

void    Game::game_player_param(iprotocol::ITCP_protocol<Client> &itcp_protocol, iprotocol::Game_player_param *param)
{
    if (param->type == iprotocol::Game_player_param::White)
        itcp_protocol.set_callback(&m_white);
    else if (param->type == iprotocol::Game_player_param::Black)
        itcp_protocol.set_callback(&m_black);
    else
        itcp_protocol.set_callback(this);
    delete param->name;
    delete param;
}

void    Game::game_param(iprotocol::ITCP_protocol<Client> &itcp_protocol, iprotocol::Game_param *param)
{
    delete param;
}

void	Game::game_start(iprotocol::ITCP_protocol<Client> &itcp_protocol)
{
    if (m_white.is_ready() == false || m_black.is_ready() == false)
        itcp_protocol.send_result(iprotocol::Error::All_player_are_not_ready);
    else
        m_is_start = true;
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
