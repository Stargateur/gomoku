//
// Select.cpp for Select in /home/plasko_a/projet/cplusplus/rtype/source/isocket
//
// Made by Antoine Plaskowski
// Login   <antoine.plaskowski@epitech.eu>
//
// Started on  Tue Dec  8 14:01:13 2015 Antoine Plaskowski
// Last update Tue Dec  8 15:50:57 2015 Antoine Plaskowski
//

#include	<algorithm>
#include	<cstring>
#include	<string>
#include	<cerrno>
#include	<iostream>
#include	"Select.hpp"

Select::Select(void) :
    m_readfds(),
    m_writefds(),
    m_nfds(-1)
{
#ifdef	_WIN32
	WSADATA wsaData;
	int err = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (err != 0)
		throw std::logic_error("fuck");
#endif
}

Select::~Select(void)
{
#ifdef	_WIN32
	WSACleanup();
#endif
}

void    Select::reset(void)
{
    FD_ZERO(&m_readfds);
    FD_ZERO(&m_writefds);
    m_nfds = -1;
}

void	Select::reset_read(ISocket const &socket)
{
#ifndef _WIN32
    if (socket.get_fd() >= FD_SETSIZE)
        throw Select_exception(strerror(EDOM));
#endif
    FD_CLR(socket.get_fd(), &m_readfds);
}

void    Select::reset_write(ISocket const &socket)
{
#ifndef _WIN32
    if (socket.get_fd() >= FD_SETSIZE)
        throw Select_exception(strerror(EDOM));
#endif
    FD_CLR(socket.get_fd(), &m_writefds);
}

bool    Select::can_read(ISocket const &socket) const
{
#ifndef _WIN32
    if (socket.get_fd() >= FD_SETSIZE)
        throw Select_exception(strerror(EDOM));
#endif
    return (FD_ISSET(socket.get_fd(), &m_readfds) != 0);
}

bool    Select::can_write(ISocket const &socket) const
{
#ifndef _WIN32
    if (socket.get_fd() >= FD_SETSIZE)
        throw Select_exception(strerror(EDOM));
#endif
    return (FD_ISSET(socket.get_fd(), &m_writefds) != 0);
}

void    Select::want_read(ISocket const &socket)
{
#ifndef _WIN32
    if (socket.get_fd() >= FD_SETSIZE)
        throw Select_exception(strerror(EDOM));
#endif
    FD_SET(socket.get_fd(), &m_readfds);
    m_nfds = std::max<int>(m_nfds, socket.get_fd());
}

void    Select::want_write(ISocket const &socket)
{
#ifndef _WIN32
    if (socket.get_fd() >= FD_SETSIZE)
        throw Select_exception(strerror(EDOM));
#endif
    FD_SET(socket.get_fd(), &m_writefds);
    m_nfds = std::max<int>(m_nfds, socket.get_fd());
}

void    Select::select(void)
{
#ifdef	_WIN32
    int ret = ::select(m_nfds + 1, &m_readfds, &m_writefds, NULL, NULL);
    if (ret == -1)
    {
        std::cerr << GetLastError() << std::endl;
        throw Select_exception("WSA error numero : " + std::to_string(GetLastError()));
    }
#else
    int ret = pselect(m_nfds + 1, &m_readfds, &m_writefds, NULL, NULL, NULL);
    if (ret == -1)
        throw Select_exception(strerror(errno));
#endif
}

void    Select::select(std::chrono::nanoseconds const &timeout)
{
#ifdef      _WIN32
    auto second = std::chrono::duration_cast<std::chrono::seconds>(timeout);
    auto mili = std::chrono::duration_cast<std::chrono::milliseconds>(timeout);
    mili -= second;
    struct timeval   time = {static_cast<long>(second.count()),static_cast<long>(mili.count())};
    int ret = ::select(m_nfds + 1, &m_readfds, &m_writefds, NULL, &time);
    if (ret == -1)
    {
        std::cerr << GetLastError() << std::endl;
        throw Select_exception("WSA error numero : " + std::to_string(GetLastError()));
    }
#else
    auto second = std::chrono::duration_cast<std::chrono::seconds>(timeout);
    auto nano = std::chrono::duration_cast<std::chrono::nanoseconds>(timeout);
    nano -= second;
    struct timespec   time = {static_cast<long>(second.count()),static_cast<long>(nano.count())};
    int ret = pselect(m_nfds + 1, &m_readfds, &m_writefds, NULL, &time, NULL);
    if (ret == -1)
        throw Select_exception(strerror(errno));
#endif /* !_WIN32 */
}

Select_exception::Select_exception(char const *what) :
    m_what(what)
{
}

Select_exception::Select_exception(std::string const &what) :
	m_what(what)
{
}

char const	*Select_exception::what(void) const noexcept
{
    return (m_what.c_str());
}
