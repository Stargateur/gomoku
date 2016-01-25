//
// ITCP_protocol.hpp for ITCP_protocol in /home/plasko_a/projet/cplusplus/rtype/include/iprotocol
// 
// Made by Antoine Plaskowski
// Login   <antoine.plaskowski@epitech.eu>
// 
// Started on  Sun Dec  6 03:35:29 2015 Antoine Plaskowski
// Last update Mon Jan 25 18:47:45 2016 Antoine Plaskowski
//

#ifndef		ITCP_PROTOCOL_HPP_
# define	ITCP_PROTOCOL_HPP_

# include	<cstdint>
# include	<string>
# include	<list>
# include	"ITime.hpp"
# include	"ITCP_client.hpp"
# include	"TCP_packet_recv.hpp"
# include	"TCP_packet_send.hpp"

template<typename T>
class	ITCP_protocol
{
public:
  enum  Error : uint8_t
  {
    NONE = 0,
      IGNORED,
      UNKNOW,
      WRONGLOGIN
  };
  class	Callback
  {
  public:
    virtual ~Callback(void);
    virtual void	result(ITCP_protocol &itcp_protocol, Error error) = 0;
    virtual void	connect(ITCP_protocol &itcp_protocol, std::string const &login, std::string const &password) = 0;
    virtual void	disconnect(ITCP_protocol &itcp_protocol) = 0;
    virtual void	ping(ITCP_protocol &itcp_protocol) = 0;
    virtual void	pong(ITCP_protocol &itcp_protocol) = 0;
  };
public:
  virtual ~ITCP_protocol(void);
  virtual bool	want_send(void) const = 0;
  virtual bool	want_recv(void) const = 0;
  virtual void	send(ITCP_client const &socket) = 0;
  virtual void	recv(ITCP_client const &socket) = 0;
  virtual void	send_result(Error error) = 0;
  virtual void	send_connect(std::string const &login, std::string const &password) = 0;
  virtual void	send_disconnect(void) = 0;
  virtual void	send_ping(void) = 0;
  virtual void	send_pong(void) = 0;
};

#endif		/* !ITCP_PROTOCOL_HPP_ */
