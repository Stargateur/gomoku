#pragma once

#include <array>
#include "ACallback.hpp"
#include "ITCP_protocol.hpp"
#include "Client.hpp"

class Arbitre : public ACallback<Client>
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
			Double_three,
			Victory
		};
		log_level(log l = None);
		log_level(const log_level &copy);
		~log_level();

		void set_log(log l);
		log get_log() const;
		log_level	operator=(const log_level &copy);
		bool	operator!=(const log_level &copy) const;
		bool	operator==(const log_level &copy) const;
		log_level operator|(const log_level &op) const;
		log_level operator&(const log_level &op) const;
	private:
		log m_l;

		int log_to_int(log l) const;
		log int_to_log(int l) const;
	};
	Arbitre(ITCP_protocol<Client>::Callback& itcp_protocol);
	Arbitre(const Arbitre &copy);
	~Arbitre(void);

	void dump(void) const;

	void set_log_level(log_level l);

	void	put_stone_game(ITCP_protocol<Client> &itcp_protocol, ITCP_protocol<Client>::Game_stone *stone);

	static const uint8_t board_size = 19;
private:
	std::array<ITCP_protocol<Client>::Game_stone::Color, board_size * board_size>	m_board;
	int			m_white_loose;
	int			m_black_loose;
	bool		m_is_black_turn;
	log_level		m_level;

	bool check_coord(int x, int y) const;

	bool check_stone_libre(int x, int y) const;

	void check_victory_five(ITCP_protocol<Client> &itcp_protocol, ITCP_protocol<Client>::Game_stone * stone);

	void	check_victory(ITCP_protocol<Client> &itcp_protocol, ITCP_protocol<Client>::Game_stone *stone);

	bool	can_capture(ITCP_protocol<Client>::Game_stone * stone, uint8_t coord[8][4]) const;

	bool	can_put_stone(ITCP_protocol<Client>::Game_stone *stone) const;

	bool	is_double_three(ITCP_protocol<Client>::Game_stone *stone) const;

	bool	check_horizontal_three(int coord[4], ITCP_protocol<Client>::Game_stone *stone) const;

	bool check_vertical_three(int coord[4], ITCP_protocol<Client>::Game_stone * stone) const;

	bool check_diag_iso_three(int coord[4], ITCP_protocol<Client>::Game_stone * stone) const;

	bool check_diag_no_iso_three(int coord[4], ITCP_protocol<Client>::Game_stone * stone) const;

	bool	is_horizontal_three(int coord[4], ITCP_protocol<Client>::Game_stone *stone) const;

	bool is_vertical_three(int coord[4], ITCP_protocol<Client>::Game_stone * stone) const;

	bool is_diag_iso_three(int coord[4], ITCP_protocol<Client>::Game_stone * stone) const;

	bool is_diag_no_iso_three(int coord[4], ITCP_protocol<Client>::Game_stone * stone) const;

	const ITCP_protocol<Client>::Game_stone::Color& operator()(unsigned int x, unsigned int y) const;

	ITCP_protocol<Client>::Game_stone::Color& operator()(unsigned int x, unsigned int y);
};