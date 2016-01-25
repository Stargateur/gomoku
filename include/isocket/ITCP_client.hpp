//
// ITCP_client.hpp for ITCP_client in /home/plasko_a/projet/cplusplus/rtype/include/server
// 
// Made by Antoine Plaskowski
// Login   <antoine.plaskowski@epitech.eu>
// 
// Started on  Fri Nov 20 05:18:04 2015 Antoine Plaskowski
// Last update Thu Dec 10 02:15:07 2015 Antoine Plaskowski
//

#ifndef		ITCP_CLIENT_HPP_
# define	ITCP_CLIENT_HPP_

# include	<cstdint>
# include	<string>
# include	"ASocket.hpp"

class	ITCP_client : virtual public ISocket
{
public:
  virtual ~ITCP_client(void);
  virtual uintmax_t	recv(uint8_t &data, uintmax_t size) const = 0;
  virtual uintmax_t	send(uint8_t const &data, uintmax_t size) const = 0;
};

class	ITCP_client_exception : public ISocket_exception
{
public:
  ITCP_client_exception(void) noexcept;
  ITCP_client_exception(ITCP_client_exception const &) noexcept;
  virtual ~ITCP_client_exception(void) noexcept;
  ITCP_client_exception	&operator=(ITCP_client_exception const &) noexcept;
};

#endif		/* !ITCP_TCP_CLIENT_HPP_ */
