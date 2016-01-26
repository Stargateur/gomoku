//
// main.cpp for main in /home/plasko_a/projet/gomoku/source/client
// 
// Made by Antoine Plaskowski
// Login   <antoine.plaskowski@epitech.eu>
// 
// Started on  Mon Jan 25 18:31:24 2016 Antoine Plaskowski
// Last update Tue Jan 26 14:07:37 2016 Antoine Plaskowski
//

#include	"Select.hpp"
#include	"TCP_protocol.hpp"
#include	"TCP_client.hpp"

class	mdr : public ITCP_protocol<int>::Callback
{
public:
  void        result(ITCP_protocol<int> &, typename ITCP_protocol<int>::Error)
  {
  }
  void        connect(ITCP_protocol<int> &, uint8_t, std::string *, std::string *)
  {
  }
  void        disconnect(ITCP_protocol<int> &)
  {
  }
  void        ping(ITCP_protocol<int> &)
  {
  }
  void        pong(ITCP_protocol<int> &)
  {
  }
  void        create_game(ITCP_protocol<int> &, typename ITCP_protocol<int>::Game *game)
  {
    std::cout << *game->name << " " << *game->owner << std::endl;
  }
};

int	main(void)
{/*
  mdr	ptdr;
  int toto;
  ITCP_protocol<int>	&lol = *new TCP_protocol<int>(&ptdr, &toto);
  ITCP_client	&xd = *new TCP_client("localhost", "4242");
  ISelect	&iselect = *new Select();

  while (42)
    {
      iselect.want_read(xd);
      iselect.select();
      if (iselect.can_read(xd))
	lol.recv(xd);
	}*/
}
