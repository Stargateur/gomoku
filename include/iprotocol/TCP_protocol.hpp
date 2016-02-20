//
// TCP_protocol.hpp for TCP_protocol in /home/plasko_a/projet/cplusplus/rtype/include/iprotocol
//
// Made by Antoine Plaskowski
// Login   <antoine.plaskowski@epitech.eu>
//
// Started on  Sun Dec  6 03:35:29 2015 Antoine Plaskowski
// Last update Thu Jan 28 10:46:22 2016 Antoine Plaskowski
//

#ifndef		TCP_PROTOCOL_HPP_
# define	TCP_PROTOCOL_HPP_

# include	<algorithm>
# include	<iostream>
# include	<cstdint>
# include	<string>
# include	<array>
# include	"ITCP_protocol.hpp"
# include	"ISelect.hpp"

template<typename T>
class	TCP_protocol : public iprotocol::ITCP_protocol<T>
{
public:
    TCP_protocol(typename iprotocol::ITCP_protocol<T>::Callback *callback, T *data) :
        m_callback(callback),
        m_data(data)
    {
        if (callback == nullptr)
            throw std::logic_error("callback can't be nullptr");
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
    void	set_callback(typename iprotocol::ITCP_protocol<T>::Callback *callback)
    {
        if (callback == nullptr)
            throw std::logic_error("callback can't be nullptr");
        m_callback = callback;
    }

public:
    typename iprotocol::ITCP_protocol<T>::Callback	*get_callback(void) const
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
        std::cerr << "je prépare un packet " << to_send->get_opcode() << std::endl;
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
            throw std::logic_error("il n'y a rien a envoyé");
        TCP_packet_send	*to_send = m_to_send.front();
	#ifndef	NDEBUG
        std::cerr << "j'envoie sur une socket client tcp " << to_send->get_opcode() << " " << std::endl;
	#endif	/* !DEBUG */
        m_to_send.pop_front();
        if (to_send->send(socket))
        {
			#ifndef	NDEBUG
            std::cerr << "Finis d'écrire" << std::endl;
			#endif	/* !DEBUG */
            delete to_send;
        }
        else
        {
			#ifndef	NDEBUG
            std::cerr << "Reste à écrire" << std::endl;
			#endif	/* !DEBUG */
        }
    }

public:
    void	recv(ITCP_client const &socket)
    {
		#ifndef	NDEBUG
        std::cerr << "je lis une socket tcp " << std::endl;
		#endif	/* !DEBUG */
        if (m_to_recv.recv(socket) == false)
            return;
		#ifndef	NDEBUG
        std::cerr << "j'ai lu un paquet tcp " << m_to_recv.get_opcode() << std::endl;
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
        case ATCP_packet::Create_game:
            recv_create_game();
            return;
        case ATCP_packet::Join_game:
            recv_join_game();
            return;
        case ATCP_packet::Leave_game:
            recv_leave_game();
            return;
        case ATCP_packet::Put_stone_game:
            recv_put_stone_game();
            return;
        case ATCP_packet::Change_param_player_game:
            recv_change_param_player_game();
            return;
        case ATCP_packet::Change_param_game:
            recv_change_param_game();
            return;
        case ATCP_packet::List_param_player_game:
            recv_list_param_player_game();
            return;
        case ATCP_packet::List_param_game:
            recv_list_param_game();
            return;
        case ATCP_packet::Game_created:
            recv_game_created();
            return;
        case ATCP_packet::Game_player_joined:
            recv_game_player_joined();
            return;
        case ATCP_packet::Game_player_left:
            recv_game_player_left();
            return;
        case ATCP_packet::Game_player_param_changed:
            recv_game_player_param_changed();
            return;
        case ATCP_packet::Game_param_changed:
            recv_game_param_changed();
            return;
        case ATCP_packet::Game_stone_put:
            recv_game_stone_put();
            return;
        case ATCP_packet::Game_deleted:
            recv_game_deleted();
            return;
        case ATCP_packet::Start_game:
            recv_start_game();
            return;
        case ATCP_packet::Ready_game:
            recv_ready_game();
            return;
        case ATCP_packet::Result_game:
            recv_result_game();
            return;
        case ATCP_packet::Message:
            recv_message();
            return;
        }
        throw std::logic_error("recv a Unknow opcode");
    }

public:
    void	send_result(typename iprotocol::ITCP_protocol<T>::Error error)
    {
        TCP_packet_send	&to_send = get_to_send(ATCP_packet::Result);;
        to_send.put(error);
    }

private:
    void	recv_result(void)
    {
        typename iprotocol::ITCP_protocol<T>::Error	error;
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
    void	send_create_game(typename iprotocol::ITCP_protocol<T>::Game const &game)
    {
        set_rec(get_to_send(ATCP_packet::Create_game), *game.name);
    }

private:
    void	recv_create_game(void)
    {
        typename iprotocol::ITCP_protocol<T>::Game	*game = new typename iprotocol::ITCP_protocol<T>::Game();
        game->name = new std::string();
        get_rec(m_to_recv, *game->name);
        m_callback->create_game(*this, game);
    }

public:
    void	send_join_game(typename iprotocol::ITCP_protocol<T>::Game const &game)
    {
        set_rec(get_to_send(ATCP_packet::Join_game), *game.name);
    }

private:
    void	recv_join_game(void)
    {
        typename iprotocol::ITCP_protocol<T>::Game	*game = new typename iprotocol::ITCP_protocol<T>::Game();
        game->name = new std::string();
        get_rec(m_to_recv, *game->name);
        m_callback->join_game(*this, game);
    }

public:
    void	send_leave_game(void)
    {
        set_rec(get_to_send(ATCP_packet::Leave_game));
    }

private:
    void	recv_leave_game(void)
    {
        m_callback->leave_game(*this);
    }

public:
    void	send_put_stone_game(typename iprotocol::ITCP_protocol<T>::Game_stone const &stone)
    {
        set_rec(get_to_send(ATCP_packet::Put_stone_game), stone.x, stone.y, stone.color);
    }

private:
    void	recv_put_stone_game(void)
    {
        typename iprotocol::ITCP_protocol<T>::Game_stone *stone = new typename iprotocol::ITCP_protocol<T>::Game_stone();
        get_rec(m_to_recv, stone->x, stone->y, stone->color);
        m_callback->put_stone_game(*this, stone);
    }

public:
    void    send_change_param_player_game(typename iprotocol::ITCP_protocol<T>::Game_player_param const &param)
    {
        set_rec(get_to_send(ATCP_packet::Change_param_player_game), *param.name, *param.value);
    }

private:
    void    recv_change_param_player_game(void)
    {
        typename iprotocol::ITCP_protocol<T>::Game_player_param *param = new typename iprotocol::ITCP_protocol<T>::Game_player_param;
        param->name = new std::string();
        param->value = new std::string();
        get_rec(m_to_recv, *param->name, *param->value);
        m_callback->change_param_player_game(*this, param);
    }

public:
    void	send_change_param_game(typename iprotocol::ITCP_protocol<T>::Game_param const &param)
    {
        set_rec(get_to_send(ATCP_packet::Change_param_game), *param.name, *param.value);
    }

private:
    void	recv_change_param_game(void)
    {
        typename iprotocol::ITCP_protocol<T>::Game_param *param = new typename iprotocol::ITCP_protocol<T>::Game_param();
        param->name = new std::string();
        param->value = new std::string();
        get_rec(m_to_recv, *param->name, *param->value);
        m_callback->change_param_game(*this, param);
    }

public:
    void    send_list_param_player_game(std::list<typename iprotocol::ITCP_protocol<T>::Game_player_param *> const &params)
    {
        TCP_packet_send &to_send = get_to_send(ATCP_packet::List_param_player_game);
        to_send.put(static_cast<uint8_t>(params.size()));
        for (auto param : params)
            set_rec(to_send, *param->name, *param->value);
    }

private:
    void    recv_list_param_player_game(void)
    {
        std::list<typename iprotocol::ITCP_protocol<T>::Game_player_param *> *params = new std::list<typename iprotocol::ITCP_protocol<T>::Game_player_param *>();
        uint8_t size;
        m_to_recv.get(size);
        for (uintmax_t i = 0; i < size; i++)
        {
            typename iprotocol::ITCP_protocol<T>::Game_player_param *param = new typename iprotocol::ITCP_protocol<T>::Game_player_param();
            param->name = new std::string();
            param->value = new std::string();
            get_rec(m_to_recv, *param->name, *param->value);
            params->push_back(param);
        }
        m_callback->list_param_player_game(*this, params);
    }

public:
    void	send_list_param_game(std::list<typename iprotocol::ITCP_protocol<T>::Game_param *> const &params)
    {
        TCP_packet_send &to_send = get_to_send(ATCP_packet::List_param_game);
        to_send.put(static_cast<uint8_t>(params.size()));
        for (auto param : params)
            set_rec(to_send, *param->name, *param->value);
    }

private:
    void	recv_list_param_game(void)
    {
        std::list<typename iprotocol::ITCP_protocol<T>::Game_param *> *params = new std::list<typename iprotocol::ITCP_protocol<T>::Game_param *>();
        uint8_t	size;
        m_to_recv.get(size);
        for (uintmax_t i = 0; i < size; i++)
        {
            typename iprotocol::ITCP_protocol<T>::Game_param *param = new typename iprotocol::ITCP_protocol<T>::Game_param();
            param->name = new std::string();
            param->value = new std::string();
            get_rec(m_to_recv, *param->name, *param->value);
            params->push_back(param);
        }
        m_callback->list_param_game(*this, params);
    }

public:
    void	send_game_created(typename iprotocol::ITCP_protocol<T>::Game const &game)
    {
        TCP_packet_send &to_send = get_to_send(ATCP_packet::Game_created);
        set_rec(to_send, *game.name);
    }

private:
    void	recv_game_created(void)
    {
        typename iprotocol::ITCP_protocol<T>::Game *game = new typename iprotocol::ITCP_protocol<T>::Game();
        game->name = new std::string();
        get_rec(m_to_recv, *game->name);
        m_callback->game_created(*this, game);
    }

public:
    void	send_game_player_joined(std::string const &name)
    {
        TCP_packet_send &to_send = get_to_send(ATCP_packet::Game_player_joined);
        set_rec(to_send, name);
    }

private:
    void	recv_game_player_joined(void)
    {
        std::string *name = new std::string();
        get_rec(m_to_recv, name);
        m_callback->game_player_joined(*this, name);
    }

public:
    void	send_game_player_left(std::string const &name)
    {
        TCP_packet_send &to_send = get_to_send(ATCP_packet::Game_player_left);
        set_rec(to_send, name);
    }

private:
    void	recv_game_player_left(void)
    {
        std::string *name = new std::string();
        get_rec(m_to_recv, name);
        m_callback->game_player_left(*this, name);
    }

public:
    void    send_game_player_param_changed(typename iprotocol::ITCP_protocol<T>::Game_player_param const &param)
    {
        TCP_packet_send &to_send = get_to_send(ATCP_packet::Game_player_param_changed);
        set_rec(to_send, *param.name, *param.value);
    }

private:
    void    recv_game_player_param_changed(void)
    {
        typename iprotocol::ITCP_protocol<T>::Game_player_param *param = new typename iprotocol::ITCP_protocol<T>::Game_player_param;
        param->name = new std::string();
        param->value = new std::string();
        get_rec(m_to_recv, *param->name, *param->value);
        m_callback->game_player_param_changed(*this, param);
    }

public:
    void	send_game_param_changed(typename iprotocol::ITCP_protocol<T>::Game_param const &param)
    {
        TCP_packet_send &to_send = get_to_send(ATCP_packet::Game_param_changed);
        set_rec(to_send, *param.name, *param.value);
    }

private:
    void	recv_game_param_changed(void)
    {
        typename iprotocol::ITCP_protocol<T>::Game_param *param = new typename iprotocol::ITCP_protocol<T>::Game_param;
        param->name = new std::string();
        param->value = new std::string();
        get_rec(m_to_recv, *param->name, *param->value);
        m_callback->game_param_changed(*this, param);
    }

public:
    void	send_game_stone_put(typename iprotocol::ITCP_protocol<T>::Game_stone const &stone)
    {
        TCP_packet_send &to_send = get_to_send(ATCP_packet::Game_stone_put);
        set_rec(to_send, stone.x, stone.y, stone.color);
    }

private:
    void	recv_game_stone_put(void)
    {
        typename iprotocol::ITCP_protocol<T>::Game_stone *stone = new typename iprotocol::ITCP_protocol<T>::Game_stone();
        get_rec(m_to_recv, stone->x, stone->y, stone->color);
        m_callback->game_stone_put(*this, stone);
    }

public:
    void	send_game_deleted(typename iprotocol::ITCP_protocol<T>::Game const &game)
    {
        TCP_packet_send &to_send = get_to_send(ATCP_packet::Game_deleted);
        set_rec(to_send, game.name);
    }

private:
    void	recv_game_deleted(void)
    {
        typename iprotocol::ITCP_protocol<T>::Game *game = new typename iprotocol::ITCP_protocol<T>::Game();
        game->name = new std::string();
        get_rec(m_to_recv, game->name);
        m_callback->game_deleted(*this, game);
    }

public:
    void	send_start_game(void)
    {
        TCP_packet_send &to_send = get_to_send(ATCP_packet::Start_game);
        set_rec(to_send);
    }

private:
    void	recv_start_game(void)
    {
        get_rec(m_to_recv);
        m_callback->start_game(*this);
    }

public:
    void	send_ready_game(bool ready)
    {
        TCP_packet_send &to_send = get_to_send(ATCP_packet::Ready_game);
        set_rec(to_send, ready);
    }

private:
    void	recv_ready_game(void)
    {
        bool	ready;
        get_rec(m_to_recv, ready);
        m_callback->ready_game(*this, ready);
    }

public:
    void	send_result_game(typename iprotocol::ITCP_protocol<T>::Game_result const &result)
    {
        TCP_packet_send &to_send = get_to_send(ATCP_packet::Result_game);
        set_rec(to_send, result.winner);
    }

private:
    void	recv_result_game(void)
    {
        typename iprotocol::ITCP_protocol<T>::Game_result *result = new typename iprotocol::ITCP_protocol<T>::Game_result();
        result->winner = new std::string();
        get_rec(m_to_recv, result->winner);
        m_callback->result_game(*this, result);
    }

public:
    void	send_message(typename iprotocol::ITCP_protocol<T>::Message const &message)
    {
        TCP_packet_send &to_send = get_to_send(ATCP_packet::Message);
        set_rec(to_send, *message.name, *message.message);
    }

private:
    void	recv_message(void)
    {
        typename iprotocol::ITCP_protocol<T>::Message *message = new typename iprotocol::ITCP_protocol<T>::Message();
        message->name = new std::string();
        message->message = new std::string();
        get_rec(m_to_recv, *message->name, *message->message);
        m_callback->message(*this, message);
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
    typename iprotocol::ITCP_protocol<T>::Callback	*m_callback;
    T	*m_data;
    TCP_packet_recv	m_to_recv;
    std::list<TCP_packet_send *>	m_to_send;
};

#endif		/* !TCP_PROTOCOL_HPP_ */
