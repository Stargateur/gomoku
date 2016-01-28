//
// Client.hpp for Client in /home/plasko_a/projet/gomoku
// 
// Made by Antoine Plaskowski
// Login   <antoine.plaskowski@epitech.eu>
// 
// Started on  Tue Jan 26 18:02:35 2016 Antoine Plaskowski
// Last update Thu Jan 28 09:34:56 2016 Antoine Plaskowski
//

#ifndef		CLIENT_HPP_
# define	CLIENT_HPP_

# include	"ITCP_client.hpp"
# include	"ITime.hpp"

struct	Client
{
  ~Client(void);
  ITCP_client	*itcp_client;
  std::string	*login;
  ITime		*last;
  bool		wait_pong;
};

#endif		/* !CLIENT_HPP_ */
