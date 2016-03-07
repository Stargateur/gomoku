#include "Arbitre.hpp"

#pragma region Log

Arbitre::log_level::log_level(Arbitre::log_level::log l) :
	m_l(l)
{}

Arbitre::log_level::log_level(const log_level & copy) :
	m_l(copy.m_l)
{
}

Arbitre::log_level::~log_level()
{}

bool Arbitre::log_level::is_active(Arbitre::log_level::log l) const
{
	return ((m_l & log_to_int(l)) != 0);
}

Arbitre::log_level Arbitre::log_level::operator=(const log_level & copy)
{
	m_l = copy.m_l;
	return *this;
}

void Arbitre::log_level::activate(Arbitre::log_level::log l)
{
	m_l |= log_to_int(l);
}

void Arbitre::log_level::desactivate(Arbitre::log_level::log l)
{
	m_l &= ~log_to_int(l);
}

int				Arbitre::log_level::log_to_int(Arbitre::log_level::log l) const
{
	switch (l)
	{
	case None:
		return (0);
	case Can_play:
		return (1);
	case Capture:
		return (2);
	case Double_three:
		return (4);
	case Victory:
		return (8);
	default:
		throw (std::logic_error("Unexpected enum"));
	}
}

#pragma endregion

#pragma region Constructeur

Arbitre::Arbitre() :
	m_level(Arbitre::log_level::None),
	m_isDoubleThreeActive(true),
	m_isFiveNotBreakableActive(true),
	m_isOnlySixActive(false)
{
}

Arbitre::Arbitre(const Arbitre & copy) :
	m_level(copy.m_level),
	m_isDoubleThreeActive(copy.m_isDoubleThreeActive),
	m_isFiveNotBreakableActive(copy.m_isFiveNotBreakableActive),
	m_isOnlySixActive(copy.m_isOnlySixActive)
{}

Arbitre::~Arbitre(void)
{}

#pragma endregion

#pragma region ArbitreLogging

void Arbitre::set_log_level(log_level l)
{
	m_level = l;
}

#pragma endregion

#pragma region Victory

Square::col	Arbitre::check_victory(const Board & b) const
{
	Square::col	ret;
	if ((ret = check_capture_victory(b)) != Square::col::None)
		return (ret);
	return (check_victory_five(b));
}

Square::col	Arbitre::check_capture_victory(const Board & b) const
{
	if (b.get_point(Square::col::Black) >= 10)
		return (Square::col::Black);
	if (b.get_point(Square::col::White) >= 10)
		return (Square::col::White);
	return (Square::col::White);
}

Square::col Arbitre::check_victory_five(const Board & b) const
{
	Square::pos	begin = { 0, 0 };
	Square::pos	end = { Board::size, Board::size };

	while (begin != end)
	{
		const std::vector<Square::Combi> &c = b.get_square(begin.first, begin.second).get_combis();
		for (auto it = c.begin(); it != c.end(); ++it)
		{
			if (it->getSize() == 5)
				return (it->getSide());
		}
		begin.first += 1;
		if (begin.first == Board::size)
		{
			begin.first = 0;
			begin.second += 1;
		}
	}
	return Square::col::None;
}

#pragma endregion

#pragma region PutStone

static bool is_three_free(const Square::Combi &c)
{
	return (c.getSize() == 3 && c.isOpenDown() == true && c.isOpenUp() == true);
}

bool Arbitre::can_put_stone(iprotocol::Game_stone * stone, const Board &b) const
{
	if (b.get_turn() != stone->color)
		return (false);
	if (b.get_square(stone->x, stone->y).get_color() != Square::col::None)
		return (false);
	if (m_isDoubleThreeActive)
	{
		Board	tmp(b);
		std::vector<iprotocol::Game_stone *> m;

		tmp.put_stone(stone->x, stone->y, stone->color, m);
		const std::vector<Square::Combi> &c = tmp.get_square(stone->x, stone->y).get_combis();
		for (auto it = c.begin(); it != c.end(); ++it)
		{
			if (is_three_free(*it))
			{
				std::pair<int, int> coeff = it->getCoeff();
				std::pair<int, int> pos = it->getBegin();
				while (pos != it->getEnd())
				{
					const std::vector<Square::Combi> &c_bis = tmp.get_square(pos.first, pos.second).get_combis();
					for (auto it_bis = c_bis.begin(); it_bis != c_bis.end(); ++it_bis)
					{
						if (is_three_free(*it_bis) && *it_bis != *it)
							return (false);
					}
					pos.first += coeff.first;
					pos.second += coeff.second;
				}
			}
		}
	}
	return (true);
}

#pragma endregion

#pragma region setterGetter

bool Arbitre::is_five_not_breakable_active() const
{
	return (m_isFiveNotBreakableActive);
}

bool Arbitre::is_double_three_active() const
{
	return (m_isDoubleThreeActive);
}

bool Arbitre::is_only_six_active() const
{
	return (m_isOnlySixActive);
}

void Arbitre::set_five_not_breakable(bool active)
{
	m_isFiveNotBreakableActive = active;
}

void Arbitre::set_double_three(bool active)
{
	m_isDoubleThreeActive = active;
}

void Arbitre::set_only_six(bool active)
{
	m_isOnlySixActive = active;
}

#pragma endregion