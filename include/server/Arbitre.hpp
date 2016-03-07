#pragma once

#include <list>
#include <array>
#include "Board.hpp"

class Arbitre
{
public:
	static bool	can_put_stone(iprotocol::Game_stone *stone, const Board &b, bool isDoubleThreeAllow);

	static Square::col check_victory(const Board &b, bool only_five, bool is_capturable);

private:
	static bool check_double_three(iprotocol::Game_stone * stone, const Board & b);

	static Square::col check_capture_victory(const Board &b);
};
