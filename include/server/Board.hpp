#pragma once

#include	<vector>
#include	"Square.hpp"

class Board
{
public:
	static const uint8_t size = 19;

	Board();
	Board(const Board &copy) = delete;
	~Board();

	Board	&operator=(const Board &copy) = delete;
	void put_stone(int x, int y, Square::col col);
	const Square	&get_square(int x, int y) const;
	Square		&get_square(int x, int y);
	int			get_pos(int x, int y) const;
	bool		is_valid(int x, int y);
	int		get_pos(Square::pos p) const;
private:
	std::vector<Square>	m_board;
};

void	aff_tab(const Board &b);
void update_line(int x, int y, std::pair<int, int> dir, Board &b);
