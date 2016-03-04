#ifndef		ACALLBACK_HPP_
# define	ACALLBACK_HPP_

# include	"ITCP_protocol.hpp"

namespace iprotocol
{
    template<typename T>
    class	ACallback : public ITCP_protocol<T>::Callback
    {
    public:
        ACallback(typename ITCP_protocol<T>::Callback &callback) :
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

        virtual void	result(ITCP_protocol<T> &itcp_protocol, Error error)
        {
            m_callback.result(itcp_protocol, error);
        }

        virtual void	connect(ITCP_protocol<T> &itcp_protocol, uint8_t version, std::string *login, std::string *password)
        {
            m_callback.connect(itcp_protocol, version, login, password);
        }

        virtual void	disconnect(ITCP_protocol<T> &itcp_protocol)
        {
            m_callback.disconnect(itcp_protocol);
        }

        virtual void	ping(ITCP_protocol<T> &itcp_protocol)
        {
            m_callback.ping(itcp_protocol);
        }

        virtual void	pong(ITCP_protocol<T> &itcp_protocol)
        {
            m_callback.pong(itcp_protocol);
        }

        virtual void	game_create(ITCP_protocol<T> &itcp_protocol, Game *game)
        {
            m_callback.game_create(itcp_protocol, game);
        }

        virtual void    game_delete(ITCP_protocol<T> &itcp_protocol, Game *game)
        {
            m_callback.game_delete(itcp_protocol, game);
        }

        virtual void	game_join(ITCP_protocol<T> &itcp_protocol, Game *game)
        {
            m_callback.game_join(itcp_protocol, game);
        }

        virtual void	game_leave(ITCP_protocol<T> &itcp_protocol)
        {
            m_callback.game_leave(itcp_protocol);
        }

        virtual void	game_stone_put(ITCP_protocol<T> &itcp_protocol, Game_stone *stone)
        {
            m_callback.game_stone_put(itcp_protocol, stone);
        }

        virtual void    game_player_param(ITCP_protocol<T> &itcp_protocol, Game_player_param *param)
        {
            m_callback.game_player_param(itcp_protocol, param);
        }

        virtual void	game_param(ITCP_protocol<T> &itcp_protocol, Game_param *param)
        {
            m_callback.game_param(itcp_protocol, param);
        }

        virtual void	game_player_join(ITCP_protocol<T> &itcp_protocol, std::string *name)
        {
            m_callback.game_player_join(itcp_protocol, name);
        }

        virtual void	game_player_leave(ITCP_protocol<T> &itcp_protocol, std::string *name)
        {
            m_callback.game_player_leave(itcp_protocol, name);
        }

        virtual void	game_start(ITCP_protocol<T> &itcp_protocol)
        {
            m_callback.game_start(itcp_protocol);
        }

        virtual void	game_ready(ITCP_protocol<T> &itcp_protocol, bool ready)
        {
            m_callback.game_ready(itcp_protocol, ready);
        }
        
        virtual void    game_score(ITCP_protocol<T> &itcp_protocol, Game_score *game_score)
        {
            m_callback.game_score(itcp_protocol, game_score);
        }

        virtual void    game_help(ITCP_protocol<T> &itcp_protocol)
        {
            m_callback.game_help(itcp_protocol);
        }

        virtual void    game_hint(ITCP_protocol<T> &itcp_protocol, Game_stone *game_stone)
        {
            m_callback.game_hint(itcp_protocol, game_stone);
        }

        virtual void	game_result(ITCP_protocol<T> &itcp_protocol, Game_result *game_result)
        {
            m_callback.game_result(itcp_protocol, game_result);
        }

        virtual void	game_message(ITCP_protocol<T> &itcp_protocol, Message *message)
        {
            m_callback.game_message(itcp_protocol, message);
        }

    protected:
        typename ITCP_protocol<T>::Callback	&m_callback;
    };
}

#endif		/* !ACALLBACK_HPP_ */
