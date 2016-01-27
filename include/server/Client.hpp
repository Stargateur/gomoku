//
// Client.hpp for Client in /home/plasko_a/projet/gomoku
// 
// Made by Antoine Plaskowski
// Login   <antoine.plaskowski@epitech.eu>
// 
// Started on  Tue Jan 26 18:02:35 2016 Antoine Plaskowski
// Last update Wed Jan 27 18:22:41 2016 Antoine Plaskowski
//

#ifndef		CLIENT_HPP_
# define	CLIENT_HPP_

# include	"ITCP_client.hpp"
# include	"ITime.hpp"

class	Client
{
public:
  Client(void);
  ~Client(void);
public:
  ITCP_client	*m_itcp_client;
  std::string	*m_login;
  ITime		*m_last;
  bool		m_wait_pong;
};

#endif		/* !CLIENT_HPP_ */
