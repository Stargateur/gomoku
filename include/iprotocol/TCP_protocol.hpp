#ifndef		TCP_PROTOCOL_HPP_
# define	TCP_PROTOCOL_HPP_

# include	<algorithm>
# include	<iostream>
# include	<cstdint>
# include	<string>
# include	<array>
# include	"ITCP_protocol.hpp"
# include	"ISelect.hpp"

namespace iprotocol
{
    class   TCP_protocol_exception : public ITCP_protocol_exception
    {
    public:
        TCP_protocol_exception(std::string &&what) noexcept;
        TCP_protocol_exception(TCP_protocol_exception const &) noexcept;
        ~TCP_protocol_exception(void) noexcept;
        char const  *what(void) const noexcept;
        TCP_protocol_exception    &operator=(TCP_protocol_exception const &) noexcept;
    public:
        std::string m_what;
    };

    template<typename T>
    class	TCP_protocol : public ITCP_protocol<T>
    {
    public:
        TCP_protocol(typename ITCP_protocol<T>::Callback *callback, T *data) :
            m_callback(callback),
            m_data(data)
        {
            if (callback == nullptr)
                throw TCP_protocol_exception("callback can't be nullptr : " + std::string(__FILE__) + " " + std::to_string(__LINE__));
        }

    public:
        ~TCP_protocol(void)
        {
            for (auto it : m_to_send)
                delete it;
            delete m_data;
        }

    public:
        uint8_t	get_version(void) const
        {
            return (1);
        }

    public:
        void	set_callback(typename ITCP_protocol<T>::Callback *callback)
        {
            if (callback == nullptr)
                throw TCP_protocol_exception("callback can't be nullptr : " + std::string(__FILE__) + " " + std::to_string(__LINE__));
            m_callback = callback;
        }

    public:
        typename ITCP_protocol<T>::Callback	*get_callback(void) const
        {
            return (m_callback);
        }

    public:
        void    set_data(T *data)
        {
            delete m_data;
            m_data = data;
        }

    public:
        T	*get_data(void)
        {
            return (m_data);
        }

    public:
        T const	*get_data(void) const
        {
            return (m_data);
        }

    private:
        TCP_packet_send	&get_to_send(ATCP_packet::Opcode opcode)
        {
            TCP_packet_send	*to_send = new TCP_packet_send();
            to_send->set_opcode(opcode);
    		#ifndef	NDEBUG
            std::cerr << "TCP_protocol : je prépare un packet " << to_send->get_opcode() << std::endl;
    		#endif	/* !DEBUG */
            m_to_send.push_back(to_send);
            return (*to_send);
        }

    public:
        bool	want_send(void) const
        {
            return (m_to_send.size() != 0);
        }

    public:
        bool	want_recv(void) const
        {
            return (true);
        }

    public:
        void	send(ITCP_client const &socket)
        {
            if (m_to_send.size() == 0)
                throw TCP_protocol_exception("nothing to send : " + std::string(__FILE__) + " " + std::to_string(__LINE__));
            TCP_packet_send	*to_send = m_to_send.front();
    	#ifndef	NDEBUG
            std::cerr << "TCP_protocol : j'envoie sur une socket client tcp " << to_send->get_opcode() << " " << std::endl;
    	#endif	/* !DEBUG */
            m_to_send.pop_front();
            if (to_send->send(socket))
            {
    			#ifndef	NDEBUG
                std::cerr << "TCP_protocol : Finis d'écrire" << std::endl;
    			#endif	/* !DEBUG */
                delete to_send;
            }
            else
            {
    			#ifndef	NDEBUG
                std::cerr << "TCP_protocol : Reste à écrire" << std::endl;
    			#endif	/* !DEBUG */
            }
        }

    public:
        void	recv(ITCP_client const &socket)
        {
    		#ifndef	NDEBUG
            std::cerr << "TCP_protocol : je lis une socket tcp " << std::endl;
    		#endif	/* !DEBUG */
            if (m_to_recv.recv(socket) == false)
                return;
    		#ifndef	NDEBUG
            std::cerr << "TCP_protocol : j'ai lu un paquet tcp " << m_to_recv.get_opcode() << std::endl;
    		#endif	/* !DEBUG */
            switch (m_to_recv.get_opcode())
            {
            case ATCP_packet::Result:
                recv_result();
                return;
            case ATCP_packet::Connect:
                recv_connect();
                return;
            case ATCP_packet::Disconnect:
                recv_disconnect();
                return;
            case ATCP_packet::Ping:
                recv_ping();
                return;
            case ATCP_packet::Pong:
                recv_pong();
                return;
            case ATCP_packet::Game_create:
                recv_game_create();
                return;
            case ATCP_packet::Game_delete:
                recv_game_delete();
                return;
            case ATCP_packet::Game_join:
                recv_game_join();
                return;
            case ATCP_packet::Game_leave:
                recv_game_leave();
                return;
            case ATCP_packet::Game_stone_put:
                recv_game_stone_put();
                return;
            case ATCP_packet::Game_param:
                recv_game_param();
                return;
            case ATCP_packet::Game_player_param:
                recv_game_player_param();
                return;
            case ATCP_packet::Game_player_join:
                recv_game_player_join();
                return;
            case ATCP_packet::Game_player_leave:
                recv_game_player_leave();
                return;
            case ATCP_packet::Game_start:
                recv_game_start();
                return;
            case ATCP_packet::Game_ready:
                recv_game_ready();
                return;
            case ATCP_packet::Game_score:
                recv_game_score();
                return;
            case ATCP_packet::Game_help:
                recv_game_help();
                return;
            case ATCP_packet::Game_hint:
                recv_game_hint();
                return;
            case ATCP_packet::Game_result:
                recv_game_result();
                return;
            case ATCP_packet::Game_message:
                recv_game_message();
                return;
            }
            throw TCP_protocol_exception("opcode unknow : " + std::string(__FILE__) + " " + std::to_string(__LINE__));
        }

    public:
        void	send_result(Error error)
        {
            TCP_packet_send	&to_send = get_to_send(ATCP_packet::Result);;
            to_send.put(error);
        }

    private:
        void	recv_result(void)
        {
            Error	error;
            m_to_recv.get(error);
            m_callback->result(*this, error);
        }

    public:
        void	send_connect(std::string const &login, std::string const &password)
        {
            TCP_packet_send	&to_send = get_to_send(ATCP_packet::Connect);
            to_send.put<uint8_t>(get_version());
            to_send.put(login);
            to_send.put(password);
        }

    private:
        void	recv_connect(void)
        {
            uint8_t version;
            std::string	*login = new std::string();
            std::string	*password = new std::string();

            m_to_recv.get(version);
            m_to_recv.get(*login);
            m_to_recv.get(*password);
            m_callback->connect(*this, version, login, password);
        }

    public:
        void	send_disconnect(void)
        {
            get_to_send(ATCP_packet::Disconnect);
        }

    private:
        void	recv_disconnect(void)
        {
            m_callback->disconnect(*this);
        }

    public:
        void	send_ping(void)
        {
            get_to_send(ATCP_packet::Ping);
        }

    private:
        void	recv_ping(void)
        {
            m_callback->ping(*this);
        }

    public:
        void	send_pong(void)
        {
            get_to_send(ATCP_packet::Pong);
        }

    private:
        void	recv_pong(void)
        {
            m_callback->pong(*this);
        }

    public:
        void	send_game_create(Game const &game)
        {
            set_rec(get_to_send(ATCP_packet::Game_create), *game.name);
        }

    private:
        void	recv_game_create(void)
        {
            Game	*game = new Game();
            game->name = new std::string();
            get_rec(m_to_recv, *game->name);
            m_callback->game_create(*this, game);
        }

    public:
        void    send_game_delete(Game const &game)
        {
            TCP_packet_send &to_send = get_to_send(ATCP_packet::Game_delete);
            set_rec(to_send, game.name);
        }

    private:
        void    recv_game_delete(void)
        {
            Game *game = new Game();
            game->name = new std::string();
            get_rec(m_to_recv, *game->name);
            m_callback->game_delete(*this, game);
        }

    public:
        void	send_game_join(Game const &game)
        {
            set_rec(get_to_send(ATCP_packet::Game_join), *game.name);
        }

    private:
        void	recv_game_join(void)
        {
            Game	*game = new Game();
            game->name = new std::string();
            get_rec(m_to_recv, *game->name);
            m_callback->game_join(*this, game);
        }

    public:
        void	send_game_leave(void)
        {
            set_rec(get_to_send(ATCP_packet::Game_leave));
        }

    private:
        void	recv_game_leave(void)
        {
            m_callback->game_leave(*this);
        }

    public:
        void    send_game_stone_put(Game_stone const &stone)
        {
            set_rec(get_to_send(ATCP_packet::Game_stone_put), stone.x, stone.y, stone.color);
        }

    private:
        void	recv_game_stone_put(void)
        {
            Game_stone *stone = new Game_stone();
            get_rec(m_to_recv, stone->x, stone->y, stone->color);
            m_callback->game_stone_put(*this, stone);
        }

    public:
        void    send_game_player_param(Game_player_param const &param)
        {
            set_rec(get_to_send(ATCP_packet::Game_player_param), *param.name, param.type);
        }

    private:
        void    recv_game_player_param(void)
        {
            Game_player_param *param = new Game_player_param;
            param->name = new std::string;
            get_rec(m_to_recv, *param->name, param->type);
            m_callback->game_player_param(*this, param);
        }

    public:
        void	send_game_param(Game_param const &param)
        {
            set_rec(get_to_send(ATCP_packet::Game_param),
                param.three_and_three, param.five_breakable, param.ai_white, param.ai_black);
        }

    private:
        void	recv_game_param(void)
        {
            Game_param *param = new Game_param();
            get_rec(m_to_recv, param->three_and_three,
            param->five_breakable, param->ai_white, param->ai_black);
            m_callback->game_param(*this, param);
        }

    public:
        void	send_game_player_join(std::string const &name)
        {
            TCP_packet_send &to_send = get_to_send(ATCP_packet::Game_player_join);
            set_rec(to_send, name);
        }

    private:
        void	recv_game_player_join(void)
        {
            std::string *name = new std::string();
            get_rec(m_to_recv, name);
            m_callback->game_player_join(*this, name);
        }

    public:
        void	send_game_player_leave(std::string const &name)
        {
            TCP_packet_send &to_send = get_to_send(ATCP_packet::Game_player_leave);
            set_rec(to_send, name);
        }

    private:
        void	recv_game_player_leave(void)
        {
            std::string *name = new std::string();
            get_rec(m_to_recv, name);
            m_callback->game_player_leave(*this, name);
        }

    public:
        void	send_game_start(void)
        {
            TCP_packet_send &to_send = get_to_send(ATCP_packet::Game_start);
            set_rec(to_send);
        }

    private:
        void	recv_game_start(void)
        {
            get_rec(m_to_recv);
            m_callback->game_start(*this);
        }

    public:
        void	send_game_ready(bool ready)
        {
            TCP_packet_send &to_send = get_to_send(ATCP_packet::Game_ready);
            set_rec(to_send, ready);
        }

    private:
        void	recv_game_ready(void)
        {
            bool	ready;
            get_rec(m_to_recv, ready);
            m_callback->game_ready(*this, ready);
        }
    
    public:
        void    send_game_score(Game_score const &score)
        {
            TCP_packet_send &to_send = get_to_send(ATCP_packet::Game_score);
            set_rec(to_send, score.white_stone_taken, score.black_stone_taken);
        }

    private:
        void    recv_game_score(void)
        {
            Game_score *score = new Game_score();
            get_rec(m_to_recv, score->white_stone_taken, score->black_stone_taken);
            m_callback->game_score(*this, score);
        }

    public:
        void    send_game_help(void)
        {
            TCP_packet_send &to_send = get_to_send(ATCP_packet::Game_help);
            set_rec(to_send);
        }

    private:
        void    recv_game_help(void)
        {
            get_rec(m_to_recv);
            m_callback->game_help(*this);
        }

    public:
        void    send_game_hint(Game_stone const &stone)
        {
            set_rec(get_to_send(ATCP_packet::Game_hint), stone.x, stone.y, stone.color);
        }

    private:
        void    recv_game_hint(void)
        {
            Game_stone *stone = new Game_stone();
            get_rec(m_to_recv, stone->x, stone->y, stone->color);
            m_callback->game_hint(*this, stone);
        }

    public:
        void    send_game_result(Game_result const &result)
        {
            TCP_packet_send &to_send = get_to_send(ATCP_packet::Game_result);
            set_rec(to_send, result.winner);
        }

    private:
        void    recv_game_result(void)
        {
            Game_result *result = new Game_result();
            get_rec(m_to_recv, result->winner);
            m_callback->game_result(*this, result);
        }
    public:
        void	send_game_message(Message const &message)
        {
            TCP_packet_send &to_send = get_to_send(ATCP_packet::Game_message);
            set_rec(to_send, *message.name, *message.message);
        }

    private:
        void	recv_game_message(void)
        {
            Message *message = new Message();
            message->name = new std::string();
            message->message = new std::string();
            get_rec(m_to_recv, *message->name, *message->message);
            m_callback->game_message(*this, message);
        }

    private:
        template<typename... Ts>
        static void	set_rec(TCP_packet_send &)
        {
        }

    private:
        template<typename Arg, typename... Args>
        static void	set_rec(TCP_packet_send &to_send, Arg &first, Args &... args)
        {
            to_send.put(first);
            set_rec(to_send, args...);
        }

    private:
        template<typename... Args>
        static void	get_rec(TCP_packet_recv &)
        {
        }

    private:
        template<typename Arg, typename... Args>
        static void	get_rec(TCP_packet_recv &to_recv, Arg &first, Args &... args)
        {
            to_recv.get(first);
            get_rec(to_recv, args...);
        }

    private:
        typename ITCP_protocol<T>::Callback	*m_callback;
        T	*m_data;
        TCP_packet_recv	m_to_recv;
        std::list<TCP_packet_send *>	m_to_send;
    };
}

#endif		/* !TCP_PROTOCOL_HPP_ */
