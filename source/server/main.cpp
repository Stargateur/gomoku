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

static void    sigint(int)
{
    std::signal(SIGINT, &sigint);
    g_keep_running = false;
}

enum lol
{
    XD
};

int	main(void)
{
	Server	server;

    std::signal(SIGINT, sigint);
    while (g_keep_running == true)
    try
    {
        server.pre_run();
        server.run();
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
