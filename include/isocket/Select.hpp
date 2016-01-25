//
// Select.hpp for Select in /home/plasko_a/projet/cplusplus/rtype/include/isocket
// 
// Made by Antoine Plaskowski
// Login   <antoine.plaskowski@epitech.eu>
// 
// Started on  Tue Dec  8 13:56:31 2015 Antoine Plaskowski
// Last update Tue Dec  8 15:48:55 2015 Antoine Plaskowski
//

#ifndef		SELECT_HPP_
# define	SELECT_HPP_

# ifdef		_WIN32
#  include	<Windows.h>
# else
#  include	<sys/select.h>
# endif
# include	"ISelect.hpp"

class	Select : public ISelect
{
public:
  Select(void);
  void	select(ITime const *timeout = nullptr);
  void	reset(void);
  bool	can_read(ISocket const &socket) const;
  bool	can_write(ISocket const &socket) const;
  void	want_read(ISocket const &socket);
  void	want_write(ISocket const &socket);
private:
  fd_set	m_readfds;
  fd_set	m_writefds;
  int	m_nfds;
};

class	Select_exception : public ISelect_exception
{
public:
  Select_exception(char const *what);
  char const	*what(void) const noexcept;
private:
  char const	*m_what;
};

#endif		/* !SELECT_HPP_ */
