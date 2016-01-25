//
// IStandard.hpp for IStandard in /home/plasko_a/projet/cplusplus/rtype/include/server
// 
// Made by Antoine Plaskowski
// Login   <antoine.plaskowski@epitech.eu>
// 
// Started on  Fri Nov 20 05:34:15 2015 Antoine Plaskowski
// Last update Thu Dec 10 02:29:23 2015 Antoine Plaskowski
//

#ifndef		ISTANDARD_HPP_
# define	ISTANDARD_HPP_

# include	<cstdint>
# include	"ASocket.hpp"

class	IStandard : virtual public ISocket
{
public:
  enum	io : uint8_t
  {
    In,
    Out,
    Err
  };
public:
  virtual	~IStandard(void);
  virtual uintmax_t	read(uint8_t &data, uintmax_t size) const = 0;
  virtual uintmax_t	write(uint8_t const &data, uintmax_t size) const = 0;
};

class	IStandard_exception : public ISocket_exception
{
public:
  IStandard_exception(void) noexcept;
  IStandard_exception(IStandard_exception const &) noexcept;
  virtual ~IStandard_exception(void) noexcept;
  IStandard_exception	&operator=(IStandard_exception const &) noexcept;
};

#endif		/* !ISTANDARD_HPP_ */
