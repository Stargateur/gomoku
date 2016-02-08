//
// main.cpp for main in /home/plasko_a/projet/gomoku/source/client
//
// Made by Antoine Plaskowski
// Login   <antoine.plaskowski@epitech.eu>
//
// Started on  Mon Jan 25 18:31:24 2016 Antoine Plaskowski
// Last update Wed Jan 27 11:29:33 2016 Antoine Plaskowski
//

#include	<iostream>
#include	<exception>
#include	<thread>
#include	<SFML/Graphics.hpp>
#include	"Client.hpp"
#include	"PlayerInfo.hpp"
#include	"GameInfo.hpp"

void start_tcpclient()
{
	std::this_thread::sleep_for(std::chrono::seconds(5));
	PlayerInfo::getInstance().lock();
	PlayerInfo::getInstance().mWantConnect = true;
	PlayerInfo::getInstance().unlock();
}

void start_ui()
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
			std::cout << "Wainting client" << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(200));
		}

		PlayerInfo::getInstance().lock();
		keepRunning = !PlayerInfo::getInstance().mWantQuit;
		PlayerInfo::getInstance().unlock();
	}
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