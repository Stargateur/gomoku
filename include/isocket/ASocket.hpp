//
// ASocket.hpp for ASocket in /home/plasko_a/projet/cplusplus/rtype/include/server
// 
// Made by Antoine Plaskowski
// Login   <antoine.plaskowski@epitech.eu>
// 
// Started on  Fri Nov 20 04:46:57 2015 Antoine Plaskowski
// Last update Thu Dec 10 16:36:21 2015 Antoine Plaskowski
//

#ifndef		ASOCKET_HPP_
# define	ASOCKET_HPP_

# include	"ISocket.hpp"
# include	"ITime.hpp"

class	ASocket : virtual public ISocket
{
public:
  ASocket(int fd);
  virtual	~ASocket(void);
  int	get_fd(void) const;
protected:
  int const	m_fd;
};

class	ASocket_exception : public ISocket_exception
{
public:
  ASocket_exception(char const *what);
  ASocket_exception(ASocket_exception const &asocket_exception) noexcept;
  virtual ~ASocket_exception(void) noexcept;
  ASocket_exception	&operator=(ASocket_exception const &asocket_exception) noexcept;
  virtual char const	*what(void) const noexcept;
private:
  char const	*m_what;
};

#endif		/* !ASOCKET_HPP_ */
