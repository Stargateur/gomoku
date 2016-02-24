#ifndef		OPTIONS_HPP_
# define	OPTIONS_HPP_

# include	<string>

struct	Options
{
	Options(void);
	std::string port;  
    bool    verbose;
};

#endif		/* !OPTIONS_HPP_ */
