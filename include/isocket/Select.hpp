#ifndef		SELECT_HPP_
# define	SELECT_HPP_

# ifdef		_WIN32
#  include	<Winsock2.h>
#  include	<Windows.h>
# else
#  include	<sys/select.h>
# endif
# include	"ISelect.hpp"

class	Select : public ISelect
{
public:
    Select(void);
	~Select(void);
    void    select(void);
    void    select(std::chrono::nanoseconds const &timeout);
    void    reset(void);
    void    reset_read(ISocket const &socket);
    void    reset_write(ISocket const &socket);
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
	Select_exception(std::string const &what);
	char const	*what(void) const noexcept;
private:
    std::string const	m_what;
};

#endif		/* !SELECT_HPP_ */
