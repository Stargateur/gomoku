//
// ISelect.hpp for ISelect in /home/plasko_a/projet/cplusplus/rtype/include/isocket
// 
// Made by Antoine Plaskowski
// Login   <antoine.plaskowski@epitech.eu>
// 
// Started on  Tue Dec  8 13:56:31 2015 Antoine Plaskowski
// Last update Thu Dec 10 02:25:19 2015 Antoine Plaskowski
//

#ifndef		ISELECT_HPP_
# define	ISELECT_HPP_

# include	"ISocket.hpp"
# include	"ITime.hpp"

class	ISelect
{
public:
  virtual ~ISelect(void);
  virtual void	select(ITime const *timeout = nullptr) = 0;
  virtual void	reset(void) = 0;
  virtual bool	can_read(ISocket const &socket) const = 0;
  virtual bool	can_write(ISocket const &socket) const = 0;
  virtual void	want_read(ISocket const &socket) = 0;
  virtual void	want_write(ISocket const &socket) = 0;
};

class	ISelect_exception : public std::exception
{
public:
  ISelect_exception(void) noexcept;
  ISelect_exception(ISelect_exception const &) noexcept;
  virtual ~ISelect_exception(void) noexcept;
  ISelect_exception	&operator=(ISelect_exception const &) noexcept;
};

#endif		/* !ISELECT_HPP_ */
