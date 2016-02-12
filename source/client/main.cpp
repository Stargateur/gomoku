//
// main.cpp for main in /home/plasko_a/projet/gomoku/source/lol
//
// Made by Antoine Plaskowski
// Login   <antoine.plaskowski@epitech.eu>
//
// Started on  Mon Jan 25 18:31:24 2016 Antoine Plaskowski
// Last update Mon Feb  8 17:43:11 2016 Antoine Plaskowski
//

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
		wantConnect = PlayerInfo::getInstance().mConnect == PlayerInfo::STATE::ASK;
		PlayerInfo::getInstance().unlock();
		if (wantConnect == true)
		{
			/*PlayerInfo::getInstance().lock();
			PlayerInfo::getInstance().mConnect = PlayerInfo::STATE::DOING;
			PlayerInfo::getInstance().unlock();*/
			try {
				Client		client;
				PlayerInfo::getInstance().lock();
				PlayerInfo::getInstance().mConnect = PlayerInfo::STATE::DONE;
				PlayerInfo::getInstance().unlock();
				std::cout << "start run" << std::endl;
				client.run();
				std::cout << "end run" << std::endl;
			}
			catch (std::exception &e) {
				PlayerInfo::getInstance().lock();
				PlayerInfo::getInstance().mConnect = PlayerInfo::STATE::FAILED;
				PlayerInfo::getInstance().mErrorMessage = "Connection error !";
				std::cout << "Error de connexion" << std::endl;
				std::cout << e.what() << std::endl;
				PlayerInfo::getInstance().unlock();
			}
		}
		else
		{
			//std::cout << "Wainting client" << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(200));
		}

		PlayerInfo::getInstance().lock();
		keepRunning = !PlayerInfo::getInstance().mQuit == PlayerInfo::STATE::ASK;
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

	// Quitting all threads
	PlayerInfo::getInstance().lock();
	PlayerInfo::getInstance().mQuit = PlayerInfo::STATE::ASK;
	PlayerInfo::getInstance().unlock();
	tcpclient.join();

	// end of program
	return (0);
}
catch (std::exception &e)
{
	std::cerr << e.what() << std::endl;
}

