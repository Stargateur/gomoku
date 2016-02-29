#ifndef		ISOCKET_HPP_
# define	ISOCKET_HPP_

# include	<exception>

class	ISocket
{
public:
    virtual	~ISocket(void);
    virtual int	get_fd(void) const = 0;
};

class	ISocket_exception : public std::exception
{
public:
    ISocket_exception(void) noexcept;
    ISocket_exception(ISocket_exception const &) noexcept;
    virtual ~ISocket_exception(void) noexcept;
    ISocket_exception	&operator=(ISocket_exception const &) noexcept;
};

#endif		/* !ISOCKET_HPP_ */
