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
#include    <csignal>
#include	"Client.hpp"

static sig_atomic_t g_keep_running = 1;

static void    sigint(int)
{
	std::signal(SIGINT, &sigint);
	g_keep_running = 0;
}

int				main(int argc, char **argv) try
{
	std::cout << argv[0] << std::endl;
	Client	client;

	std::signal(SIGINT, sigint);
	while (g_keep_running != 0)
	{
		client.pre_run();
		client.run();
	}
	return (0);
}
catch (std::exception &e)
{
	std::cerr << e.what() << std::endl;
}

