//
// Client.hpp for Client in /home/plasko_a/projet/gomoku
// 
// Made by Antoine Plaskowski
// Login   <antoine.plaskowski@epitech.eu>
// 
// Started on  Tue Jan 26 18:02:35 2016 Antoine Plaskowski
// Last update Tue Jan 26 20:13:04 2016 Antoine Plaskowski
//

#ifndef		CLIENT_HPP_
# define	CLIENT_HPP_

# include	"ITCP_client.hpp"

class	Client
{
public:
  Client(ITCP_client *itcp_client = nullptr);
  ~Client(void);
public:
  ITCP_client	*m_itcp_client;
  std::string	*m_login;
};

#endif		/* !CLIENT_HPP_ */
