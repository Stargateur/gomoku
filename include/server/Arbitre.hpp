#pragma once

#include <list>
#include <array>
#include "Board.hpp"

class Arbitre
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
	Arbitre();
	Arbitre(const Arbitre &copy);
	~Arbitre();

	void set_log_level(log_level l);

	Square::col		check_victory(const Board &b) const;

	bool			can_put_stone(iprotocol::Game_stone *stone, const Board &b) const;

	bool			is_five_not_breakable_active() const;
	bool			is_double_three_active() const;
	bool			is_only_six_active() const;

	void			set_five_not_breakable(bool active);
	void			set_double_three(bool active);
	void			set_only_six(bool active);

	static const uint8_t board_size = 19;
private:
	log_level		m_level;
	bool			m_isFiveNotBreakableActive;
	bool			m_isDoubleThreeActive;
	bool			m_isOnlySixActive;

	Square::col check_victory_five(const Board &b) const;

	Square::col check_capture_victory(const Board &b) const;
};
