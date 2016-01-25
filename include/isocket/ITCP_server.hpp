//
// ITCP_server.hpp for ITCP_server in /home/plasko_a/projet/cplusplus/rtype/include/server
// 
// Made by Antoine Plaskowski
// Login   <antoine.plaskowski@epitech.eu>
// 
// Started on  Fri Nov 20 05:13:59 2015 Antoine Plaskowski
// Last update Thu Dec 10 02:18:35 2015 Antoine Plaskowski
//

#ifndef		ITCP_SERVER_HPP_
# define	ITCP_SERVER_HPP_

# include	"ASocket.hpp"
# include	"ITCP_client.hpp"

class	ITCP_server : virtual public ISocket
{
public:
  virtual ~ITCP_server(void);
  virtual ITCP_client	&accept(void) const = 0;
};

class	ITCP_server_exception : public ISocket_exception
{
public:
  ITCP_server_exception(void) noexcept;
  ITCP_server_exception(ITCP_server_exception const &) noexcept;
  virtual ~ITCP_server_exception(void) noexcept;
  ITCP_server_exception	&operator=(ITCP_server_exception const &) noexcept;
};

#endif		/* !ITCP_SERVER_HPP_ */
