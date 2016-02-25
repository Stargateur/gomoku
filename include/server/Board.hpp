#pragma once

#include	<vector>
#include	"Square.hpp"

class Board
{
public:
	static const uint8_t size = 19;

	Board();
	~Board();

	void put_stone(uint8_t x, uint8_t y, Square::col col);
	const Square	&get_square(uint8_t x, uint8_t y) const;
private:
	Square		&get_square(uint8_t x, uint8_t y);
	bool		is_valid(uint8_t x, uint8_t y);
	uint8_t		get_pos(uint8_t x, uint8_t y);
	uint8_t		get_pos(Square::pos p);
	std::vector<Square>	m_board;
};

