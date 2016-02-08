//
// main.cpp for main in /home/plasko_a/projet/gomoku/source/lol
//
// Made by Antoine Plaskowski
// Login   <antoine.plaskowski@epitech.eu>
//
// Started on  Mon Jan 25 18:31:24 2016 Antoine Plaskowski
// Last update Mon Feb  8 17:43:11 2016 Antoine Plaskowski
//

#if 0
#include	<iostream>
#include	<exception>
#include	<thread>
#include	<SFML/Graphics.hpp>
#include	"Client.hpp"
#include	"PlayerInfo.hpp"
#include	"GameInfo.hpp"
#include	"GomokuGraphics.hpp"

void start_tcpclient()
{
	bool	keepRunning = true;
	bool	wantConnect = false;

	while (keepRunning == true)
	{
		PlayerInfo::getInstance().lock();
		wantConnect = PlayerInfo::getInstance().mWantConnect;
		PlayerInfo::getInstance().unlock();
		if (wantConnect == true)
		{
			try {
				Client		client;
				client.run();
			}
			catch (std::exception &e) {
				PlayerInfo::getInstance().lock();
				PlayerInfo::getInstance().mHasFailed = true;
				PlayerInfo::getInstance().mErrorMessage = "Connection failed !";
				PlayerInfo::getInstance().unlock();
				std::cout << "Error de connexion" << std::endl;
			}
		}
		else
		{
			//std::cout << "Wainting client" << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(200));
		}

		PlayerInfo::getInstance().lock();
		keepRunning = !PlayerInfo::getInstance().mWantQuit;
		PlayerInfo::getInstance().unlock();
	}
}

void start_ui()
{
	GomokuGraphics gui;

	gui.init();
	gui.run();
}

int				main(void) try
{
	// Initing memory
	PlayerInfo::getInstance();
	GameInfo::getInstance();

	// Launching main tasks
	std::thread	tcpclient(start_tcpclient);
	start_ui();

	// Waiting for all threads
	tcpclient.join();

	// end of program
	return (0);
}
catch (std::exception &e)
{
	std::cerr << e.what() << std::endl;
}
#else

#include	<iostream>
#include	"TCP_protocol.hpp"
#include	"TCP_client.hpp"
#include	"Select.hpp"
#include	"Time.hpp"

std::string color = "";

class lol : public ITCP_protocol<ITCP_client>::Callback
{
private:
	ITCP_protocol<ITCP_client>	*m_itcp_protocol;
    ISelect	*m_iselect;
public:
lol(void) :
    m_itcp_protocol(new TCP_protocol<ITCP_client>(this, new TCP_client("localhost", "4242"))),
    m_iselect(new Select)
{
    m_itcp_protocol->send_connect("plasko_a", "plasko_a");
    std::string name;

    std::cin >> name;
    ITCP_protocol<ITCP_client>::Game    game = {&name};
	std::string s = "";
	while (s != "j" && s != "c")
	{
		std::cout << "connexion(j/c)" << std::endl;
		std::cin >> s;
	}
	if (s == "c")
		m_itcp_protocol->send_create_game(game);
	else
		m_itcp_protocol->send_join_game(game);
	std::cin >> color;
    ITCP_protocol<ITCP_client>::Game_player_param	param;
    std::string ptdr("color");
    param.name = &ptdr;
    param.value = &color;
    m_itcp_protocol->send_change_param_player_game(param);
}

~lol(void)
{
}

void	run(void)
{
    bool	g_keep_running = true;

    while (g_keep_running == true)
    {
    	Time timeout(1);
        m_iselect->reset();
        if (m_itcp_protocol->want_recv() == true)
            m_iselect->want_read(*m_itcp_protocol->get_data());
        if (m_itcp_protocol->want_send() == true)
            m_iselect->want_write(*m_itcp_protocol->get_data());	    	
        std::string envoye;
        std::cout << "y or n ?" << std::endl;
        std::cin >> envoye;
        if (envoye == "y")
        {
    		std::string x;
    		std::string y;
    		std::cout << "x puis y" << std::endl;
    		std::cin >> x >> y;
    		ITCP_protocol<ITCP_client>::Game_stone stone;
    		stone.x = stoull(x);
    		stone.y = stoull(y);
    			std::cout << color << std::endl;
    		if (color == "white")
    		{
	    		stone.color = ITCP_protocol<ITCP_client>::Game_stone::White;
	    	}
	    	else
	    		stone.color = ITCP_protocol<ITCP_client>::Game_stone::Black;
	    	m_itcp_protocol->send_put_stone_game(stone);
	    }
	   	m_iselect->select(timeout);
	    if (m_iselect->can_read(*m_itcp_protocol->get_data()) == true)
		{
			m_iselect->reset_read(*m_itcp_protocol->get_data());
            m_itcp_protocol->recv(*m_itcp_protocol->get_data());
		}
        if (m_iselect->can_write(*m_itcp_protocol->get_data()) == true)
		{
			m_iselect->reset_write(*m_itcp_protocol->get_data());
            m_itcp_protocol->send(*m_itcp_protocol->get_data());
		}
    }
}

void	result(ITCP_protocol<ITCP_client> &itcp_protocol, typename ITCP_protocol<ITCP_client>::Error error)
{
    std::cout << error << std::endl;
}

void	connect(ITCP_protocol<ITCP_client> &itcp_protocol, uint8_t version, std::string *login, std::string *password)
{
}

void	disconnect(ITCP_protocol<ITCP_client> &itcp_protocol)
{
}

void	ping(ITCP_protocol<ITCP_client> &itcp_protocol)
{
    itcp_protocol.send_pong();
}

void	pong(ITCP_protocol<ITCP_client> &itcp_protocol)
{
}

void	create_game(ITCP_protocol<ITCP_client> &itcp_protocol, typename ITCP_protocol<ITCP_client>::Game *game)
{
}

void	join_game(ITCP_protocol<ITCP_client> &itcp_protocol, typename ITCP_protocol<ITCP_client>::Game *game)
{
}

void	leave_game(ITCP_protocol<ITCP_client> &itcp_protocol)
{
}

void	put_stone_game(ITCP_protocol<ITCP_client> &itcp_protocol, typename ITCP_protocol<ITCP_client>::Game_stone *stone)
{
}

void	change_param_player_game(ITCP_protocol<ITCP_client> &itcp_protocol, typename ITCP_protocol<ITCP_client>::Game_player_param *param)
{
}

void    change_param_game(ITCP_protocol<ITCP_client> &itcp_protocol, typename ITCP_protocol<ITCP_client>::Game_param *param)
{
}

void    list_param_game(ITCP_protocol<ITCP_client> &itcp_protocol, std::list<typename ITCP_protocol<ITCP_client>::Game_param *> *params)
{
}

void    list_param_player_game(ITCP_protocol<ITCP_client> &itcp_protocol, std::list<typename ITCP_protocol<ITCP_client>::Game_player_param *> *params)
{
}

void	game_created(ITCP_protocol<ITCP_client> &itcp_protocol, typename ITCP_protocol<ITCP_client>::Game *game)
{
}

void	game_player_joined(ITCP_protocol<ITCP_client> &itcp_protocol, std::string *name)
{
}

void	game_player_left(ITCP_protocol<ITCP_client> &itcp_protocol, std::string *name)
{
}

void    game_player_param_changed(ITCP_protocol<ITCP_client> &itcp_protocol, typename ITCP_protocol<ITCP_client>::Game_player_param *param)
{
}

void	game_param_changed(ITCP_protocol<ITCP_client> &itcp_protocol, typename ITCP_protocol<ITCP_client>::Game_param *param)
{
}

void	game_stone_put(ITCP_protocol<ITCP_client> &itcp_protocol, typename ITCP_protocol<ITCP_client>::Game_stone *stone)
{
}

void	game_deleted(ITCP_protocol<ITCP_client> &itcp_protocol, typename ITCP_protocol<ITCP_client>::Game *game)
{
}

void	start_game(ITCP_protocol<ITCP_client> &itcp_protocol)
{
}

void	ready_game(ITCP_protocol<ITCP_client> &itcp_protocol, bool ready)
{
}

void	result_game(ITCP_protocol<ITCP_client> &itcp_protocol, typename ITCP_protocol<ITCP_client>::Game_result *game_result)
{
}

void	message(ITCP_protocol<ITCP_client> &itcp_protocol, typename ITCP_protocol<ITCP_client>::Message *message)
{
}
};

int	main(void)
{
  lol	lol;

  lol.run();
}
#endif
