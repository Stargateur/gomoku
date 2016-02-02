//
// Time.cpp for  in /home/bbr2394/renduTek3/cpp_spider/source
//
// Made by Bertrand-Rapello Baptiste
// Login   <bertra_l@epitech.net>
//
// Started on  Wed Oct 21 21:04:15 2015 Bertrand-Rapello Baptiste
// Last update Sat Jan 30 00:19:18 2016 Antoine Plaskowski
//

#include    <stdexcept>
#include    <cerrno>
#include    <string.h>
#include    "Time.hpp"

#ifdef _WIN32
# include <ctime>
#endif

Time::Time(intmax_t second, intmax_t nano) :
#ifdef _WIN32
    m_second(second),
    m_milli(nano / milli_by_nano)
#else
    m_timespec({second, nano})
#endif
{
}

intmax_t	Time::get_second(void) const
{
#ifdef _WIN32
    return (m_second);
#else
    return (m_timespec.tv_sec);
#endif
}

void	Time::set_second(intmax_t second)
{
#ifdef _WIN32
    m_second = second;
#else
    m_timespec.tv_sec = second;
#endif
}

intmax_t	Time::get_nano(void) const
{
#ifdef _WIN32
    return (m_milli * milli_by_nano);
#else
    return (m_timespec.tv_nsec);
#endif
}

void	Time::set_nano(intmax_t nano)
{
#ifdef _WIN32
    m_milli = nano / milli_by_nano;
#else
    m_timespec.tv_nsec = nano;
#endif
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

Time::~Time(void)
{
}

#ifdef _WIN32
extern "C" __declspec(dllexport)
#endif /* !_WIN32 */
ITime   *new_itime(void)
{
    return (new Time());
}

void    Time::now(void)
{
#ifdef  _WIN32
    SYSTEMTIME SystemTime;
    m_second = time(NULL);
    GetSystemTime(&SystemTime);
    m_milli = SystemTime.wMilliseconds;
#else
    if (clock_gettime(CLOCK_REALTIME, &m_timespec) == -1)
        throw std::logic_error(::strerror(errno));
#endif
}

ITime	&Time::clone(void) const
{
    return (*new Time(get_second(), get_nano()));
}
