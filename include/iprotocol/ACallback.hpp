//
// ACallback.hpp for ACallback in /home/plasko_a/projet/gomoku
//
// Made by Antoine Plaskowski
// Login   <antoine.plaskowski@epitech.eu>
//
// Started on  Wed Jan 27 14:45:21 2016 Antoine Plaskowski
// Last update Thu Jan 28 10:24:53 2016 Antoine Plaskowski
//

#ifndef		ACALLBACK_HPP_
# define	ACALLBACK_HPP_

# include	"ITCP_protocol.hpp"

template<typename T>
class	ACallback : public iprotocol::ITCP_protocol<T>::Callback
{
public:
    ACallback(typename iprotocol::ITCP_protocol<T>::Callback &callback) :
        m_callback(callback)
    {
    }

    ACallback(ACallback const &acallback) :
        m_callback(acallback.m_callback)
    {

    }
    ~ACallback(void)
    {
    }

    virtual void	result(iprotocol::ITCP_protocol<T> &itcp_protocol, iprotocol::Error error)
    {
        m_callback.result(itcp_protocol, error);
    }

    virtual void	connect(iprotocol::ITCP_protocol<T> &itcp_protocol, uint8_t version, std::string *login, std::string *password)
    {
        m_callback.connect(itcp_protocol, version, login, password);
    }

    virtual void	disconnect(iprotocol::ITCP_protocol<T> &itcp_protocol)
    {
        m_callback.disconnect(itcp_protocol);
    }

    virtual void	ping(iprotocol::ITCP_protocol<T> &itcp_protocol)
    {
        m_callback.ping(itcp_protocol);
    }

    virtual void	pong(iprotocol::ITCP_protocol<T> &itcp_protocol)
    {
        m_callback.pong(itcp_protocol);
    }

    virtual void	create_game(iprotocol::ITCP_protocol<T> &itcp_protocol, iprotocol::Game *game)
    {
        m_callback.create_game(itcp_protocol, game);
    }

    virtual void	join_game(iprotocol::ITCP_protocol<T> &itcp_protocol, iprotocol::Game *game)
    {
        m_callback.join_game(itcp_protocol, game);
    }

    virtual void	leave_game(iprotocol::ITCP_protocol<T> &itcp_protocol)
    {
        m_callback.leave_game(itcp_protocol);
    }

    virtual void	put_stone_game(iprotocol::ITCP_protocol<T> &itcp_protocol, iprotocol::Game_stone *stone)
    {
        m_callback.put_stone_game(itcp_protocol, stone);
    }

    virtual void    change_param_player_game(iprotocol::ITCP_protocol<T> &itcp_protocol, iprotocol::Game_player_param *param)
    {
        m_callback.change_param_player_game(itcp_protocol, param);
    }

    virtual void	change_param_game(iprotocol::ITCP_protocol<T> &itcp_protocol, iprotocol::Game_param *param)
    {
        m_callback.change_param_game(itcp_protocol, param);
    }

    virtual void    list_param_player_game(iprotocol::ITCP_protocol<T> &itcp_protocol, std::list<iprotocol::Game_player_param *> *params)
    {
        m_callback.list_param_player_game(itcp_protocol, params);
    }

    virtual void	list_param_game(iprotocol::ITCP_protocol<T> &itcp_protocol, std::list<iprotocol::Game_param *> *params)
    {
        m_callback.list_param_game(itcp_protocol, params);
    }

    virtual void	game_created(iprotocol::ITCP_protocol<T> &itcp_protocol, iprotocol::Game *game)
    {
        m_callback.game_created(itcp_protocol, game);
    }

    virtual void	game_player_joined(iprotocol::ITCP_protocol<T> &itcp_protocol, std::string *name)
    {
        m_callback.game_player_joined(itcp_protocol, name);
    }

    virtual void	game_player_left(iprotocol::ITCP_protocol<T> &itcp_protocol, std::string *name)
    {
        m_callback.game_player_left(itcp_protocol, name);
    }

    virtual void    game_player_param_changed(iprotocol::ITCP_protocol<T> &itcp_protocol, iprotocol::Game_player_param *param)
    {
        m_callback.game_player_param_changed(itcp_protocol, param);
    }

    virtual void	game_param_changed(iprotocol::ITCP_protocol<T> &itcp_protocol, iprotocol::Game_param *param)
    {
        m_callback.game_param_changed(itcp_protocol, param);
    }

    virtual void	game_stone_put(iprotocol::ITCP_protocol<T> &itcp_protocol, iprotocol::Game_stone *stone)
    {
        m_callback.game_stone_put(itcp_protocol, stone);
    }

    virtual void	game_deleted(iprotocol::ITCP_protocol<T> &itcp_protocol, iprotocol::Game *game)
    {
        m_callback.game_deleted(itcp_protocol, game);
    }

    virtual void	start_game(iprotocol::ITCP_protocol<T> &itcp_protocol)
    {
        m_callback.start_game(itcp_protocol);
    }

    virtual void	ready_game(iprotocol::ITCP_protocol<T> &itcp_protocol, bool ready)
    {
        m_callback.ready_game(itcp_protocol, ready);
    }

    virtual void	result_game(iprotocol::ITCP_protocol<T> &itcp_protocol, iprotocol::Game_result *game_result)
    {
        m_callback.result_game(itcp_protocol, game_result);
    }

    virtual void	message(iprotocol::ITCP_protocol<T> &itcp_protocol, iprotocol::Message *message)
    {
        m_callback.message(itcp_protocol, message);
    }

protected:
    typename iprotocol::ITCP_protocol<T>::Callback	&m_callback;
};

#endif		/* !ACALLBACK_HPP_ */
