//
// main.cpp for main in /home/plasko_a/projet/gomoku/source/server
// 
// Made by Antoine Plaskowski
// Login   <antoine.plaskowski@epitech.eu>
// 
// Started on  Mon Jan 25 18:31:09 2016 Antoine Plaskowski
// Last update Mon Jan 25 21:13:24 2016 Antoine Plaskowski
//

#include	"TCP_protocol.hpp"

int	main(void)
{
  ITCP_protocol<int>	&lol = *new TCP_protocol<int>(nullptr, nullptr);

  int toto;
  lol.set_data(&toto);
  *lol.get_data() = 5;
  std::cout << toto << std::endl;
}
