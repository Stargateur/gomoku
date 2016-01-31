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
#include <SFML/Graphics.hpp>
#include	"Client.hpp"

int	main(void) try
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}

    Client	client;

    client.run();
}
catch (std::exception &e)
{
	std::cerr << e.what() << std::endl;
}