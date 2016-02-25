#include "Board.hpp"
#include <array>


Board::Board() :
	m_board()
{
	for (uint8_t x = 0; x < Board::size; x++)
	{
		for (uint8_t y = 0; y < Board::size; y++)
		{
			m_board.push_back(Square(std::make_pair(x, y)));
		}
	}
}


Board::~Board()
{
}

void Board::put_stone(uint8_t x, uint8_t y, Square::col col)
{
	m_board[x * Board::size + y].put_stone(col);
}

const Square & Board::get_square(uint8_t x, uint8_t y) const
{
	return (m_board[x * Board::size + y]);
}

Square & Board::get_square(uint8_t x, uint8_t y)
{
	return (m_board[x * Board::size + y]);
}

bool Board::is_valid(uint8_t x, uint8_t y)
{
	return (x < Board::size && x > 0 &&
		y < Board::size && y > 0);
}

uint8_t Board::get_pos(uint8_t x, uint8_t y)
{
	return (x * Board::size + y);
}

uint8_t Board::get_pos(Square::pos p)
{
	return (p.first * Board::size + p.second);
}
