#ifndef		ISELECT_HPP_
# define	ISELECT_HPP_

# include   <chrono>
# include	"ISocket.hpp"

class	ISelect
{
public:
    virtual ~ISelect(void);
    virtual void	select(void) = 0;
    virtual void    select(std::chrono::nanoseconds const &timeout) = 0;
    virtual void    reset(void) = 0;
    virtual void    reset_read(ISocket const &socket) = 0;
    virtual void    reset_write(ISocket const &socket) = 0;
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
