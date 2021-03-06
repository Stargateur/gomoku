#include "Board.hpp"
#include <array>

# include <iostream>

const uint8_t	Board::size = 19;

void aff_tab(const Board &b)
{
	for (int i = 0; i < Board::size; i++)
	{
		for (int j = 0; j < Board::size; j++)
		{
			const Square &s = b.get_square(i, j);
			if (s.get_combis().size() > 0)
			{
				std::cout << "Square : " << i << " " << j << " " << (s.get_color() == Square::col::None ? "" : (s.get_color() == Square::col::White ? "White" : "Black")) << std::endl;
			}
			for (auto it = s.get_combis().begin(); it != s.get_combis().end(); ++it)
			{
				std::cout << (*it).getBegin().first << "-" << (*it).getBegin().second << " " << (*it).getEnd().first << "-" << (*it).getEnd().second << std::endl;
			}
		}
	}
}

Board::Board() :
	m_point({ {Square::col::Black, 0}, { Square::col::White, 0 } }),
	m_turn(Square::col::Black),
	m_board()
{
	for (int x = 0; x < Board::size; x++)
	{
		for (int y = 0; y < Board::size; y++)
		{
			m_board.push_back(Square(std::make_pair(x, y)));
		}
	}
}

Board::Board(const Board & copy) :
	m_point(copy.m_point),
	m_turn(copy.m_turn),
	m_board(copy.m_board)
{
}

Board::~Board()
{
}

void get_border(int x, int y, const std::pair<int, int> &dir, const Board &b, Square::pos &start, Square::pos &end)
{
	Square::col			side = b.get_square(x, y).get_color();
	bool isBroken = false;
	int					new_x = x;
	int					new_y = y;

	while (b.is_valid(new_x, new_y) && (b.get_square(new_x, new_y).get_color() == side))
	{
		new_x -= dir.first;
		new_y -= dir.second;
	}
	if (b.is_valid(new_x, new_y) && (b.get_square(new_x, new_y).get_color() == Square::col::None))
	{
		start.first = new_x;
		start.second = new_y;
	}
	else
	{
		start.first = new_x + dir.first;
		start.second = new_y + dir.second;
	}
	new_x = x;
	new_y = y;
	while (b.is_valid(new_x, new_y) && (isBroken == false || b.get_square(new_x, new_y).get_color() == side))
	{
		if (b.get_square(new_x, new_y).get_color() == Square::col::None && b.is_valid(new_x + dir.first, new_y + dir.second) && b.get_square(new_x + dir.first, new_y + dir.second).get_color() == side)
			isBroken = true;
		else if (b.get_square(new_x, new_y).get_color() != side)
			break;
		new_x += dir.first;
		new_y += dir.second;
	}
	if (b.is_valid(new_x, new_y) && b.get_square(new_x, new_y).get_color() == Square::col::None)
	{
		end.first = new_x;
		end.second = new_y;
	}
	else
	{
		end.first = new_x - dir.first;
		end.second = new_y - dir.second;
	}
}

void update_line(int x, int y, std::pair<int, int> dir, Board &b)
{
	Square::col			side = b.get_square(x, y).get_color();
	std::array<int, 2>	direction =
	{
		1,
		-1
	};
	for (int j = 0; j < 2; j++)
	{
		if (side == Square::col::None)
		{
			int new_x = x + dir.first * direction[j];
			int new_y = y + dir.second * direction[j];
			if (b.is_valid(new_x, new_y) && b.get_square(new_x, new_y).get_color() != Square::col::None)
				b.get_square(new_x, new_y).update(b);
		}
		else
		{
			std::pair<int, int> start;
			std::pair<int, int> end;
			int					new_x = x;
			int					new_y = y;
			std::pair<int, int> new_dir = dir;

			new_dir.first *= direction[j];
			new_dir.second *= direction[j];
			get_border(x, y, dir, b, start, end);
			new_x = start.first;
			new_y = start.second;
			while (new_x != end.first || new_y != end.second)
			{
				Square &s = b.get_square(new_x, new_y);
				s.update(Square::Combi(start, end, b));
				new_x += dir.first;
				new_y += dir.second;
			}
			b.get_square(new_x, new_y).update(Square::Combi(start, end, b));
		}
	}
}

bool can_capture(int x, int y, Square::col col, std::vector<Square::Combi> &Combi, const Board &b)
{
	if (col == Square::col::None)
		return (false);
	const std::vector<Square::Combi> &c = b.get_square(x, y).get_combis();
	for (auto it = c.begin(); it != c.end(); ++it)
	{
		if (it->getSize() == 2 && it->isBroken() == false)
		{
			if (std::make_pair(x, y) == it->getBegin())
			{
				if (b.is_valid(it->getEnd().first + it->getCoeff().first, it->getEnd().second + it->getCoeff().second) && b.get_square(it->getEnd().first + it->getCoeff().first, it->getEnd().second + it->getCoeff().second).get_color() == col)
					Combi.push_back(*it);
			}
			else
			{
				if (b.is_valid(it->getBegin().first - it->getCoeff().first, it->getBegin().second - it->getCoeff().second))
				{
					Square::col c = b.get_square(it->getBegin().first - it->getCoeff().first, it->getBegin().second - it->getCoeff().second).get_color();
					if (c == col)
						Combi.push_back(*it);
				}
			}
		}
	}
	return (Combi.size() != 0);
}

void Board::put_stone(int x, int y, Square::col col, std::vector<iprotocol::Game_stone *> &movement)
{
	std::array<std::pair<int, int>, 8> dir =
	{
		std::make_pair(0, 1),
		std::make_pair(0, -1),
		std::make_pair(1, 1),
		std::make_pair(1, -1),
		std::make_pair(-1, 1),
		std::make_pair(-1, -1),
		std::make_pair(1, 0),
		std::make_pair(-1, 0)
	};
	std::vector<std::pair<int, int>>	toUpdate;
	get_square(x, y).put_stone(col);
	movement.push_back(new iprotocol::Game_stone(x, y, col));
	std::vector<Square::Combi> t;
	if (can_capture(x, y, col, t, *this))
	{
		for (auto it = t.begin(); it != t.end(); ++it)
		{
			Square::pos p = it->getBegin();
			Square::pos end = it->getEnd();
			while (p != end)
			{
				if (get_square(p.first, p.second).get_color() == it->getSide())
				{
					put_stone(p.first, p.second, Square::col::None, movement);
					movement.push_back(new iprotocol::Game_stone(p.first, p.second, Square::col::None));
				}
				p.first += it->getCoeff().first;
				p.second += it->getCoeff().second;
			}
			if (get_square(p.first, p.second).get_color() == it->getSide())
			{
				put_stone(p.first, p.second, Square::col::None, movement);
				movement.push_back(new iprotocol::Game_stone(p.first, p.second, Square::col::None));
			}
		}
	}
	for (int k = 0; k < 8; ++k)
	{
		if (is_valid(x + dir[k].first, y + dir[k].second))
			toUpdate.push_back(std::make_pair(x + dir[k].first, y + dir[k].second));
	}
	for (auto it = toUpdate.begin(); it != toUpdate.end(); ++it)
	{
		get_square(it->first, it->second).update(*this);
	}
	if (m_turn == Square::col::White)
		m_turn = Square::col::Black;
	else
		m_turn = Square::col::White;
}

const Square & Board::get_square(int x, int y) const
{
	return (m_board[get_pos(x, y)]);
}

Square & Board::get_square(int x, int y)
{
	return (m_board[get_pos(x, y)]);
}

bool Board::is_valid(int x, int y) const
{
	return (x < Board::size && x >= 0 &&
		y < Board::size && y >= 0);
}

int Board::get_pos(int x, int y) const
{
	return (x * Board::size + y);
}

int Board::get_pos(Square::pos p) const
{
	return (p.first * Board::size + p.second);
}

int Board::get_point(Square::col col) const
{
	return (m_point.at(col));
}

Square::col Board::get_turn() const
{
	return m_turn;
}
