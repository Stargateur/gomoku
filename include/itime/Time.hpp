//
// Time.hpp for Time.hpp in /home/plasko_a/projet/cplusplus/rtype
// 
// Made by Antoine Plaskowski
// Login   <plasko_a@epitech.eu>
// 
// Started on  Sun Dec 27 01:06:19 2015 Antoine Plaskowski
// Last update Sun Dec 27 20:25:12 2015 Antoine Plaskowski
//

#ifndef TIME_HPP_
# define TIME_HPP_

# include	<ctime>
# include	<cstdint>
# include	"ITime.hpp"

class Time : public ITime
{
public:
  Time(intmax_t second = 0, intmax_t nano = 0);
  ~Time(void);
public:
  static const Time	second;
  intmax_t	get_second(void) const;
  void	set_second(intmax_t second);
  intmax_t	get_nano(void) const;
  void	set_nano(intmax_t nano);
  bool	now(void);
  ITime	&clone(void) const;
private:
  struct timespec	m_timespec;  
};

#endif	/* !TIME_HPP_ */
