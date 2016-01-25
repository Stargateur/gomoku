//
// Time_Windows.cpp for Time_Windows in /home/plasko_a/projet/cplusplus/rtype
// 
// Made by Antoine Plaskowski
// Login   <plasko_a@epitech.eu>
// 
// Started on  Sun Dec 27 01:00:23 2015 Antoine Plaskowski
// Last update Sun Dec 27 02:05:24 2015 Antoine Plaskowski
//

#include <ctime>
#include "Time_Windows.hpp"

Time::Time(void)
{
}

intmax_t	Time::get_second(void) const
{
  return (m_second);
}

void	Time::set_second(intmax_t second)
{
  m_second = second;
}

intmax_t	Time::get_nano(void) const
{
  return (m_milli * milli_by_nano);
}

void	Time::set_nano(intmax_t nano)
{
  m_milli = nano / milli_by_nano;
  if (get_nano() >= ITime::nano_by_second)
    {
      if (get_second() >= 0)
	set_second(get_second() + 1);
      else
	set_second(get_second() - 1);
      set_nano(get_nano() - ITime::nano_by_second);
    }
  else if (get_nano() < 0)
    {
      if (get_second() >= 0)
	set_second(get_second() - 1);
      else        set_second(get_second() + 1);
      set_nano(get_nano() + ITime::nano_by_second);
    }
}

bool	Time::now(void)
{
  SYSTEMTIME SystemTime;
  m_second = time(NULL);
  GetSystemTime(&SystemTime);
  m_milli = SystemTime.wMilliseconds;
  return (false);
}

ITime	&Time::clone(void) const
{
  return (*new Time());
}

Time::~Time(void)
{
}

extern "C" __declspec(dllexport)
ITime	*new_itime(void)
{
  return (new Time());
}
