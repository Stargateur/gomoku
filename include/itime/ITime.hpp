#ifndef	ITIME_HPP_
# define	ITIME_HPP_

# include	<cstdint>

class	ITime
{
public:
    intmax_t const	nano_by_second = 1000000000;
public:
    ITime(void);
    ITime(ITime const &);
    virtual ~ITime(void);
    ITime	&operator=(ITime const &itime);
    ITime	&operator+=(ITime const &itime);
    ITime	&operator-=(ITime const &itime);
    virtual intmax_t	get_second(void) const = 0;
    virtual void	set_second(intmax_t) = 0;
    virtual intmax_t	get_nano(void) const = 0;
    virtual void	set_nano(intmax_t) = 0;
    virtual void	now(void) = 0;
    virtual ITime	&clone(void) const = 0;
};

bool	operator!=(ITime const &lhs, ITime const &rhs);
bool	operator==(ITime const &lhs, ITime const &rhs);
bool	operator<(ITime const &lhs, ITime const &rhs);
bool	operator>(ITime const &lhs, ITime const &rhs);
bool	operator<=(ITime const &lhs, ITime const &rhs);
bool	operator>=(ITime const &lhs, ITime const &rhs);

class	ITimeException
{
public:
    virtual char const *what(void) const noexcept = 0;
    virtual ~ITimeException(void);
};

extern "C"
{
# define	NAME_FCT_NEW_ITIME	"new_itime"
#ifdef __linux__
    ITime	*new_itime(void);
#else
    __declspec(dllexport) ITime	*new_itime(void);
#endif
    typedef	ITime *(*fct_new_itime)(void);
    typedef	ITime *(&ref_new_itime)(void);
}

#endif /* !ITIME_HPP_ */
