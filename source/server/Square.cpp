#include "Square.hpp"
#include "Board.hpp"

#include <cassert>
#include <algorithm>

#include <iostream>

Square::Square(const pos &pos) :
	m_pos(pos),
	m_col(col::None),
	m_combis()
{
}

Square::Square(const Square & copy) :
	m_pos(copy.m_pos),
	m_col(copy.m_col),
	m_combis(copy.m_combis)
{
}

Square::~Square()
{
}

/*
@TODO gerer les egalites de combinaisons
*/
bool Square::operator==(const Square & other) const
{
	return (get_pos() == other.get_pos() &&
		get_color() == other.get_color());
}

bool Square::operator!=(const Square & other) const
{
	return (!((*this) == other));
}

bool Square::operator==(pos & other) const
{
	return (get_pos() == other);
}

bool Square::operator!=(pos & other) const
{
	return (!((*this) == other));
}

void Square::put_stone(col new_color)
{
	m_col = new_color;
}

/*
@TODO fusionner les deux tableaux et supprimer les anciennes combinaisons reecrasee
*/
void Square::update(const Combi &newCombi)
{
	for (auto it = m_combis.begin(); it < m_combis.end(); ++it)
	{
		if (it->isInclude(newCombi))
		{
			*it = newCombi;
			return;
		}
	}
	m_combis.push_back(newCombi);
}

void Square::update(Board &b)
{
	std::vector<std::pair<int, int> > tab =
	{
		std::make_pair(0, 1),
		std::make_pair(1, 1),
		std::make_pair(1, -1),
		std::make_pair(1, 0)
	};
	for (auto it = m_combis.begin(); it != m_combis.end(); ++it)
	{
		std::remove(tab.begin(), tab.end(), it->getCoeff());
		bool val = it->check_validity(b);
		if (!(val))
		{
			std::pair<int, int> coeff = it->getCoeff();
			delete_line(coeff, b);
			update_line(m_pos.first, m_pos.second, coeff, b);
			update(b);
			return;
		}
	}
	for (auto it = tab.begin(); it != tab.end(); ++it)
	{
		update_line(m_pos.first, m_pos.second, *it, b);
	}
}

void Square::delete_line(std::pair<int, int> coeff, Board &b)
{
//	std::cout << "coeff : " << coeff.first << "-" << coeff.second << " " << m_pos.first << "-" << m_pos.second << std::endl;
	auto it = m_combis.begin();
	while (it != m_combis.end())
	{
		if (it->getCoeff() == coeff)
		{
			std::pair<int, int> pos = it->getBegin();
			std::pair<int, int> end = it->getEnd();
			std::pair<int, int> coeff = it->getCoeff();
			Combi c = *it;

			it = m_combis.erase(it);
			while (pos != end)
			{
				b.get_square(pos.first, pos.second).delete_combi(c);
//				b.get_square(pos.first, pos.second).update(Combi(std::make_pair(pos.first, pos.second), std::make_pair(pos.first, pos.second), b, coeff));
				pos.first += coeff.first;
				pos.second += coeff.second;
			}
			b.get_square(pos.first, pos.second).delete_combi(c);
		}
		else
		{
			++it;
		}
	}
//	std::cout << std::endl;
}

void Square::delete_combi(const Combi & combi)
{
	auto it = m_combis.begin();

	while (it != m_combis.end())
	{
		if (*it == combi)
			it = m_combis.erase(it);
		else
			++it;
	}
}

Square::col Square::get_color() const
{
	return (m_col);
}

Square::pos Square::get_pos() const
{
	return (m_pos);
}

const std::vector<Square::Combi> &Square::get_combis() const
{
	return (m_combis);
}

int		Square::Combi::get_index(pos p)
{
	return (p.first * Board::size + p.second);
}

Square::Combi::Combi(pos begin, pos end, const Board & board, std::pair<int, int> coeff) :
	Square::Combi(begin, end, board)
{
	m_coeff = coeff;
}

Square::Combi::Combi(pos begin, pos end, const Board & board) :
	m_begin(begin),
	m_end(end),
	m_size(0),
	m_isBroken(false),
	m_isOpenUp(false),
	m_isOpenDown(false),
	m_side(Square::col::None),
	m_coeff()
{
	if (get_index(m_begin) > get_index(m_end))
	{
		m_begin = end;
		m_end = begin;
	}
	m_coeff.first = m_end.first - m_begin.first;
	m_coeff.second = m_end.second - m_begin.second;
	if (m_coeff.first != 0)
		m_coeff.first /= std::abs(m_coeff.first);
	if (m_coeff.second != 0)
		m_coeff.second /= std::abs(m_coeff.second);

	pos tmp = m_begin;

	while (tmp != m_end)
	{
		if (board.get_square(tmp.first, tmp.second).get_color() == Square::col::None)
		{
			if (tmp == m_begin)
				m_isOpenUp = true;
			else
				m_isBroken = true;
		}
		else
		{
			m_size++;
			m_side = board.get_square(tmp.first, tmp.second).get_color();
		}
		if (tmp.first < m_end.first)
			tmp.first++;
		else if (tmp.first > m_end.first)
			tmp.first--;
		if (tmp.second < m_end.second)
			tmp.second++;
		else if (tmp.second > m_end.second)
			tmp.second--;
	}
	if (board.get_square(tmp.first, tmp.second).get_color() == Square::col::None)
		m_isOpenDown = true;
	else m_size++;
}

Square::Combi::Combi(Combi const & other) :
	m_begin(other.m_begin),
	m_end(other.m_end),
	m_size(other.m_size),
	m_isBroken(other.m_isBroken),
	m_isOpenUp(other.m_isOpenUp),
	m_isOpenDown(other.m_isOpenDown),
	m_side(other.m_side),
	m_coeff(other.m_coeff)
{
}

Square::Combi::~Combi()
{
}

Square::Combi Square::Combi::operator=(const Combi & other)
{
	m_begin = other.m_begin;
	m_end = other.m_end;
	m_size = other.m_size;
	m_isBroken = other.m_isBroken;
	m_isOpenUp = other.m_isOpenUp;
	m_isOpenDown = other.m_isOpenDown;
	m_side = other.m_side;
	m_coeff = other.m_coeff;
	return (*this);
}

bool Square::Combi::operator==(const Combi & other) const
{
	return (m_begin == other.m_begin &&
		m_end == other.m_end &&
		m_size == other.m_size &&
		m_isBroken == other.m_isBroken &&
		m_isOpenUp == other.m_isOpenUp &&
		m_isOpenDown == other.m_isOpenDown &&
		m_side == other.m_side &&
		m_coeff == other.m_coeff
		);
}

bool Square::Combi::operator!=(const Combi & other) const
{
	return (!((*this) == other));
}

bool Square::Combi::check_validity(const Board &b) const
{
	/*	std::pair<int, int> coeff = getCoeff();
		std::pair<int, int> start = m_begin;
		std::pair<int, int> end = m_end;

		if (m_isOpenUp)
		{
			if (b.get_square(m_begin.first, m_begin.second).get_color() != Square::col::None)
			{
				std::cerr << "NotFreeUp" << std::endl;
				return (false);
			}
			start.first += coeff.first;
			start.second += coeff.second;
		}
		if (m_isOpenDown)
		{
			if (b.get_square(m_end.first, m_end.second).get_color() != Square::col::None)
			{
				std::cerr << "NotFreeDown" << std::endl;
				return (false);
			}
			end.first -= coeff.first;
			end.second -= coeff.second;
		}

		int x = m_begin.first;
		int y = m_begin.second;
		bool isBroken = false;

		while (x != end.first || y != end.second)
		{
			const Square &s = b.get_square(x, y);
			if (s.get_color() == Square::col::None && isBroken == true)
			{
				std::cerr << "ALreadyBroken" << std::endl;
				return (false);
			}
			else if (s.get_color() == Square::col::None)
				isBroken = true;
			else if (s.get_color() != m_side)
			{
				std::cerr << "NoSide" << std::endl;
				return (false);
			}
			x += coeff.first;
			y += coeff.second;
		}
		return (m_isBroken == isBroken);*/
	Square::pos begin = m_begin;
	Square::pos end = m_end;
	Square::pos p = m_begin;


	if (begin == end)
	{
		return (m_begin == m_end);
	}
	if (b.get_square(p.first, p.second).get_color() == Square::col::None)
	{
		p.first += m_coeff.first;
		p.second += m_coeff.second;
	}
	get_border(p.first, p.second, m_coeff, b, begin, end);
	return (*this == Combi(begin, end, b));
}

std::pair<int, int>	Square::Combi::getCoeff() const
{
//	assert(m_coeff != std::make_pair(0, 0));
	return (m_coeff);
}

bool	Square::Combi::isInclude(Combi newCombi)
{
	return (*this == newCombi);
	/*	int deltaX = (m_end.first - m_begin.first);
		if (deltaX != 0)
			deltaX /= std::abs(deltaX);
		int deltaAX = (newCombi.m_end.first - newCombi.m_begin.first);
		if (deltaAX != 0)
			deltaAX /= std::abs(deltaAX);
		int deltaY = (m_end.second - m_begin.second);
		if (deltaY != 0)
			deltaY /= std::abs(deltaY);
		int deltaAY = (newCombi.m_end.second - newCombi.m_begin.second);
		if (deltaAY != 0)
			deltaAY /= std::abs(deltaAY);

		if (deltaX != deltaAX || deltaY != deltaAY)
			return (false);
		unsigned int deltaADX = std::abs(newCombi.m_end.first - newCombi.m_begin.first);
		unsigned int deltaADY = std::abs(newCombi.m_end.second - newCombi.m_begin.second);
		unsigned int deltaABX = std::abs(m_begin.first - newCombi.m_begin.first);
		unsigned int deltaACX = std::abs(m_end.first - newCombi.m_begin.first);
		unsigned int deltaABY = std::abs(m_begin.second - newCombi.m_begin.second);
		unsigned int deltaACY = std::abs(m_end.second - newCombi.m_begin.second);
		return (deltaABX <= deltaADX && deltaACX <= deltaADX && deltaABY <= deltaADY && deltaACY <= deltaADY);*/
}

const Square::pos &Square::Combi::getBegin() const
{
	return (m_begin);
}

const Square::pos &Square::Combi::getEnd() const
{
	return (m_end);
}

int Square::Combi::getSize() const
{
	return (m_size);
}

bool Square::Combi::isBroken() const
{
	return (m_isBroken);
}

bool Square::Combi::isOpenUp() const
{
	return (m_isOpenUp);
}

bool Square::Combi::isOpenDown() const
{
	return (m_isOpenDown);
}

Square::col	Square::Combi::getSide() const
{
	return (m_side);
}