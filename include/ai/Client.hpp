//
// Client.hpp for Client in /home/plasko_a/projet/gomoku/include
//
// Made by Antoine Plaskowski
// Login   <antoine.plaskowski@epitech.eu>
//
// Started on  Wed Jan 27 11:00:32 2016 Antoine Plaskowski
// Last update Wed Jan 27 11:18:31 2016 Antoine Plaskowski
//

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
	void	pre_run(void);
    void	run(void);
    void	result(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol, iprotocol::Error error);
    void	connect(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol, uint8_t version, std::string *login, std::string *password);
    void	disconnect(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol);
    void	ping(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol);
    void	pong(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol);
    void	create_game(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol, typename iprotocol::ITCP_protocol<ITCP_client>::Game *game);
    void	join_game(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol, typename iprotocol::ITCP_protocol<ITCP_client>::Game *game);
    void	leave_game(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol);
    void	put_stone_game(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol, typename iprotocol::ITCP_protocol<ITCP_client>::Game_stone *stone);
    void    change_param_player_game(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol, typename iprotocol::ITCP_protocol<ITCP_client>::Game_player_param *param);
    void    change_param_game(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol, typename iprotocol::ITCP_protocol<ITCP_client>::Game_param *param);
    void    list_param_player_game(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol, std::list<typename iprotocol::ITCP_protocol<ITCP_client>::Game_player_param *> *params);
    void    list_param_game(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol, std::list<typename iprotocol::ITCP_protocol<ITCP_client>::Game_param *> *params);
    void	game_created(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol, typename iprotocol::ITCP_protocol<ITCP_client>::Game *game);
    void	game_player_joined(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol, std::string *name);
    void	game_player_left(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol, std::string *name);
    void    game_player_param_changed(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol, typename iprotocol::ITCP_protocol<ITCP_client>::Game_player_param *param);
    void    game_param_changed(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol, typename iprotocol::ITCP_protocol<ITCP_client>::Game_param *param);
    void	game_stone_put(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol, typename iprotocol::ITCP_protocol<ITCP_client>::Game_stone *stone);
    void	game_deleted(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol, typename iprotocol::ITCP_protocol<ITCP_client>::Game *game);
    void	start_game(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol);
    void	ready_game(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol, bool ready);
    void	result_game(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol, typename iprotocol::ITCP_protocol<ITCP_client>::Game_result *game_result);
    void	message(iprotocol::ITCP_protocol<ITCP_client> &itcp_protocol, typename iprotocol::ITCP_protocol<ITCP_client>::Message *message);
private:
    iprotocol::ITCP_protocol<ITCP_client>						*m_itcp_protocol;
    ISelect											*m_iselect;
	std::list<iprotocol::ITCP_protocol<ITCP_client>::Game *>	mRoomlist;
};

#endif		/* !CLIENT_HPP_ */
