#pragma once

#include <list>
#include <array>
#include "ACallback.hpp"
#include "ITCP_protocol.hpp"
#include "Client.hpp"

class Arbitre : public iprotocol::ACallback<Client>
{
public:
	class log_level
	{
	public:
		enum log : uint8_t
		{
			None,
			Can_play,
			Capture,
			Double_three ,
			Victory
		};
		log_level(log l = None);
		log_level(const log_level &copy);
		~log_level();

		void activate(log l);
		void desactivate(log l);
		bool is_active(log l) const;
		log_level	operator=(const log_level &copy);
	private:
		int m_l;

		int log_to_int(log l) const;
	};
	Arbitre(iprotocol::ITCP_protocol<Client>::Callback& itcp_protocol);
	Arbitre(const Arbitre &copy);
	~Arbitre(void);

	void dump(void) const;
	void Welcome(iprotocol::ITCP_protocol<Client> &itcp_protocol);

	void set_log_level(log_level l);

	void	put_stone_game(iprotocol::ITCP_protocol<Client> &itcp_protocol, iprotocol::Game_stone *stone);

	static const uint8_t board_size = 19;
private:
	std::array<iprotocol::Game_stone::Color, board_size * board_size>	m_board;
	std::list<std::pair<int, int> > m_empty_square;
	int			m_white_loose;
	int			m_black_loose;
	bool		m_is_black_turn;
	log_level		m_level;

	bool check_coord(int x, int y) const;

	bool check_stone_libre(int x, int y) const;

	void check_victory_five(iprotocol::ITCP_protocol<Client> &itcp_protocol, iprotocol::Game_stone * stone);

	void	check_victory(iprotocol::ITCP_protocol<Client> &itcp_protocol, iprotocol::Game_stone *stone);

	bool	can_capture(iprotocol::Game_stone * stone, uint8_t coord[8][4]) const;

	bool	can_put_stone(iprotocol::Game_stone *stone) const;

	bool is_three_line(iprotocol::Game_stone * stone, const std::pair<int, int>& coeff, std::array<std::pair<int, int>, 2> &coords) const;

	bool is_three(iprotocol::Game_stone * stone) const;

	const iprotocol::Game_stone::Color& operator()(unsigned int x, unsigned int y) const;

	iprotocol::Game_stone::Color& operator()(unsigned int x, unsigned int y);
};