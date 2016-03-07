#pragma once

#include	<vector>
#include	<map>
#include	"Square.hpp"

class Board
{
public:
	static const uint8_t size;

	Board();
	Board(const Board &copy);
	~Board();

	Board	&operator=(const Board &copy) = delete;
	void put_stone(int x, int y, Square::col col, std::vector<iprotocol::Game_stone *> &movement);
	const Square	&get_square(int x, int y) const;
	Square		&get_square(int x, int y);
	int			get_pos(int x, int y) const;
	bool		is_valid(int x, int y);
	int		get_pos(Square::pos p) const;
	int		get_point(Square::col col) const;
	Square::col	get_turn() const;
private:
	std::map<Square::col, int> m_point;
	Square::col			m_turn;
	std::vector<Square>	m_board;
};

void	aff_tab(const Board &b);
void update_line(int x, int y, std::pair<int, int> dir, Board &b);
