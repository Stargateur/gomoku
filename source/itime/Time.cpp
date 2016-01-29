//
// Time.cpp for  in /home/bbr2394/renduTek3/cpp_spider/source
//
// Made by Bertrand-Rapello Baptiste
// Login   <bertra_l@epitech.net>
//
// Started on  Wed Oct 21 21:04:15 2015 Bertrand-Rapello Baptiste
// Last update Fri Jan 29 23:58:54 2016 Antoine Plaskowski
//

#include "Time.hpp"

#ifdef _WIN32

# include <ctime>

Time::Time(intmax_t second, intmax_t nano) :
    m_second(second),
    m_milli(nano / milli_by_nano)
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

extern "C" __declspec(dllexport)
ITime	*new_itime(void)
{
    return (new Time());
}

# else

Time::Time(intmax_t second, intmax_t nano) :
    m_timespec({second, nano})
{
}

Time::~Time(void)
{
}

intmax_t	Time::get_second(void) const
{
    return (m_timespec.tv_sec);
}

void	Time::set_second(intmax_t second)
{
    m_timespec.tv_sec = second;
}

intmax_t	Time::get_nano(void) const
{
    return (m_timespec.tv_nsec);
}

void	Time::set_nano(intmax_t nano)
{
    m_timespec.tv_nsec = nano;
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
        else
            set_second(get_second() + 1);
        set_nano(get_nano() + ITime::nano_by_second);
    }
}

bool	Time::now(void)
{
    if (clock_gettime(CLOCK_REALTIME, &m_timespec) == -1)
        return true;
    return false;
}

ITime	*new_itime(void)
{
    return (new Time());
}

#endif // WIN32

ITime	&Time::clone(void) const
{
    return (*new Time(get_second(), get_nano()));
}
