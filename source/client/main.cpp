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
#include	<mutex>
#include	<SFML/Graphics.hpp>
#include	"Client.hpp"
#include	"PlayerInfo.hpp"
#include	"GameInfo.hpp"

std::mutex	PlayerInfoMutex;
std::mutex	GameInfoMutex;

void init_graph()
{
	std::this_thread::sleep_for(std::chrono::seconds(5));
}

int				main(void) try
{
	// Initing memory
	PlayerInfo::getInstance();

	// Launching main tasks
	std::thread	graph(init_graph);

	// Waiting for all threads
	graph.join();

	// end of program
	return (0);
}
catch (std::exception &e)
{
	std::cerr << e.what() << std::endl;
}