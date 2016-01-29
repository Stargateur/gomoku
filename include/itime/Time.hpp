//
// Time.hpp for Time.hpp in /home/plasko_a/projet/cplusplus/rtype
//
// Made by Antoine Plaskowski
// Login   <plasko_a@epitech.eu>
//
// Started on  Sun Dec 27 01:06:19 2015 Antoine Plaskowski
// Last update Sat Jan 30 00:13:12 2016 Antoine Plaskowski
//

#ifndef TIME_HPP_
# define TIME_HPP_

# include	<ctime>
# ifdef _WIN32
#  include	<windows.h>
# endif /* !_WIN32 */
# include	<cstdint>
# include	"ITime.hpp"

class Time : public ITime
{
public:
    Time(intmax_t second = 0, intmax_t nano = 0);
    ~Time(void);
public:
    intmax_t	get_second(void) const;
    void	set_second(intmax_t second);
    intmax_t	get_nano(void) const;
    void	set_nano(intmax_t nano);
    bool	now(void);
    ITime	&clone(void) const;
private:
#ifdef _WIN32
  static const uintmax_t milli_by_nano = 1000;
    time_t	m_second;
    WORD	m_milli;
#else
    struct timespec	m_timespec;
#endif  
};

#endif // _WIN32
