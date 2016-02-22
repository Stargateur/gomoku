//
// Client.hpp for Client in /home/plasko_a/projet/gomoku
//
// Made by Antoine Plaskowski
// Login   <antoine.plaskowski@epitech.eu>
//
// Started on  Tue Jan 26 18:02:35 2016 Antoine Plaskowski
// Last update Thu Jan 28 09:34:56 2016 Antoine Plaskowski
//

#ifndef		CLIENT_HPP_
# define	CLIENT_HPP_

# include   <chrono>
# include	"ITCP_client.hpp"

class	Client
{
public:
	Client(ITCP_client *itcp_client, std::string *login);
    ~Client(void);
    void	set_itcp_client(ITCP_client *itcp_client);
    ITCP_client const	*get_itcp_client(void) const;
    ITCP_client	*get_itcp_client(void);
    void	set_login(std::string *login);
    std::string const	*get_login(void) const;
    std::string	*get_login(void);
    std::chrono::steady_clock::time_point const	&get_last(void) const;
    std::chrono::steady_clock::time_point	&get_last(void);
    void	set_wait_pong(bool wait_pong);
    bool	get_wait_pong(void) const;
    void    add_error(void);
    uintmax_t   get_error(void) const;
private:
    ITCP_client	*m_itcp_client;
    std::string	*m_login;
    std::chrono::steady_clock::time_point		m_last;
    bool		m_wait_pong;
    uintmax_t   m_error;
};

std::ostream &operator<<(std::ostream &os, Client const &client);

#endif		/* !CLIENT_HPP_ */
