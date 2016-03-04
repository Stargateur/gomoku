#ifndef		CLIENT_HPP_
# define	CLIENT_HPP_

# include	"ITCP_protocol.hpp"
# include	"ITCP_client.hpp"
# include	"ISelect.hpp"

class Client : public iprotocol::ITCP_protocol<ITCP_client>::Callback
{
public:
    Client(void);
    ~Client(void);
    void	run(void);
    void	result(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol, iprotocol::Error error);
    void	connect(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol, uint8_t version, std::string *login, std::string *password);
    void	disconnect(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol);
    void	ping(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol);
    void	pong(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol);
    void	game_create(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol, typename iprotocol::Game *game);
    void    game_delete(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol, typename iprotocol::Game *game);
    void	game_join(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol, typename iprotocol::Game *game);
    void	game_leave(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol);
    void	game_stone_put(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol, typename iprotocol::Game_stone *stone);
    void    game_player_param(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol, typename iprotocol::Game_player_param *param);
    void    game_param(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol, typename iprotocol::Game_param *param);
    void	game_player_join(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol, std::string *name);
    void	game_player_leave(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol, std::string *name);
    void	game_start(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol);
    void	game_ready(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol, bool ready);
    void    game_score(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol, typename iprotocol::Game_score *game_score);
    void    game_help(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol);
    void    game_hint(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol, typename iprotocol::Game_stone *game_stone);
    void    game_result(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol, typename iprotocol::Game_result *game_result);
    void	game_message(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol, typename iprotocol::Message *message);
private:
    iprotocol::ITCP_protocol<ITCP_client>						*m_itcp_protocol;
    ISelect											*m_iselect;
	std::list<iprotocol::Game *>	mRoomlist;

private:
	void	checkUserInputs(void);
};

#endif		/* !CLIENT_HPP_ */
