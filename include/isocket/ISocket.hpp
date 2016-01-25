//
// ISocket.hpp for ISocket in /home/plasko_a/projet/cplusplus/rtype/include/server
// 
// Made by Antoine Plaskowski
// Login   <antoine.plaskowski@epitech.eu>
// 
// Started on  Fri Nov 20 04:45:20 2015 Antoine Plaskowski
// Last update Thu Dec 10 02:16:16 2015 Antoine Plaskowski
//

#ifndef		ISOCKET_HPP_
# define	ISOCKET_HPP_

# include	<exception>

class	ISocket
{
public:
  virtual	~ISocket(void);
  virtual int	get_fd(void) const = 0;
};

class	ISocket_exception : public std::exception
{
public:
  ISocket_exception(void) noexcept;
  ISocket_exception(ISocket_exception const &) noexcept;
  virtual ~ISocket_exception(void) noexcept;
  ISocket_exception	&operator=(ISocket_exception const &) noexcept;
};

#endif		/* !ISOCKET_HPP_ */
