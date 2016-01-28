//
// main.cpp for main in /home/plasko_a/projet/gomoku/source/server
//
// Made by Antoine Plaskowski
// Login   <antoine.plaskowski@epitech.eu>
//
// Started on  Mon Jan 25 18:31:09 2016 Antoine Plaskowski
// Last update Thu Jan 28 16:33:33 2016 Antoine Plaskowski
//

#include	<iostream>
#include	"Server.hpp"

int	main(void) try
{
	    Server	server;

    	server.run();
}
catch (std::exception &e)
{
	std::cerr << e.what() << std::endl;
}