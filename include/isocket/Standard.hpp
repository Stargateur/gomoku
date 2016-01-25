//
// Standard.hpp for Standard in /home/plasko_a/projet/cplusplus/rtype/include/server
// 
// Made by Antoine Plaskowski
// Login   <antoine.plaskowski@epitech.eu>
// 
// Started on  Fri Nov 20 05:36:07 2015 Antoine Plaskowski
// Last update Tue Dec  8 15:39:15 2015 Antoine Plaskowski
//

#ifndef		STANDARD_HPP_
# define	STANDARD_HPP_

# include	"IStandard.hpp"

class	Standard : public ASocket, public IStandard
{
public:
  Standard(IStandard::io io);
  uintmax_t	read(uint8_t &data, uintmax_t size) const;
  uintmax_t	write(uint8_t const &data, uintmax_t size) const;
private:
  int	io_to_fd(IStandard::io io);
};

class	Standard_exception : public IStandard_exception
{
public:
  Standard_exception(char const *what);
  char const	*what(void) const noexcept;
private:
  char const	*m_what;
};

#endif		/* !STANDARD_HPP_ */
