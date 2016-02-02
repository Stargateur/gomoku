//
// main.cpp for main in /home/plasko_a/projet/gomoku/source/server
//
// Made by Antoine Plaskowski
// Login   <antoine.plaskowski@epitech.eu>
//
// Started on  Mon Jan 25 18:31:09 2016 Antoine Plaskowski
// Last update Thu Jan 28 16:33:33 2016 Antoine Plaskowski
//

#include    <iostream>
#include    <csignal>
#include	"Server.hpp"

static sig_atomic_t g_keep_running = true;

void    sigint(int)
{
    g_keep_running = false;
    std::signal(SIGINT, &sigint);
}

int	main(void) try
{
	Server	server;

    std::signal(SIGINT, &sigint);
    while (g_keep_running == true)
    {
        server.pre_run();
        server.run();
    }
    std::cout << "ok" << std::endl;
    return 0;
}
catch (std::exception &e)
{
	std::cerr << "bonjour " << e.what() << std::endl;
}