//
// main.cpp for main in /home/plasko_a/projet/gomoku/source/server
//
// Made by Antoine Plaskowski
// Login   <antoine.plaskowski@epitech.eu>
//
// Started on  Mon Jan 25 18:31:09 2016 Antoine Plaskowski
// Last update Sat Feb 13 02:24:46 2016 Antoine Plaskowski
//

#include    <iostream>
#include    <csignal>
#include	<chrono>
#include	"Server.hpp"

static sig_atomic_t g_keep_running = 1;

static void    sigint(int)
{
    std::signal(SIGINT, &sigint);
    g_keep_running = 0;
}

int	main(void)
{
  auto start = std::chrono::steady_clock::now();
  Server	server;
    std::signal(SIGINT, sigint);
    while (g_keep_running != 0)
    try
    {
        server.pre_run();
        server.run();
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
	auto end = std::chrono::steady_clock::now();
	auto diff = end - start;
	auto lol = std::chrono::duration_cast<std::chrono::seconds>(diff);
	diff -= lol;
	std::cout << lol.count() << " s" << std::chrono::duration_cast<std::chrono::nanoseconds>(diff).count() << " n" << std::endl;
    return 0;
}
