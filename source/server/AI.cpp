#include    <iostream>
#include    "AI.hpp"
#include    "Arbitre.hpp"

void	AI::utils(Board const &board, std::vector<position> &pos)
{
	position	i;
	for (i.x = 0; i.x < Board::size; i.x++)
		for (i.y = 0; i.y < Board::size; i.y++)
		{
			iprotocol::Game_stone	stone(i.x, i.y, board.get_turn());
			if (Arbitre::can_put_stone(&stone, board, false))
				pos.push_back(i);
		}
}

void	AI::utils(Board &board, std::vector<position> &pos, position const &i)
{
	std::vector<iprotocol::Game_stone *>	movement;
	board.put_stone(i.x, i.y, board.get_turn(), movement);
	for (iprotocol::Game_stone *stone : movement)
	{
		auto it = pos.begin();
		while (it != pos.end())
			if (it->x == stone->x && it->y == stone->y)
				it = pos.erase(it);
			else
				it++;
	}
}

void	AI::play(Board const &board, iprotocol::Game_stone &stone_final, uintmax_t n)
{
	std::random_device rd;
	std::default_random_engine	gen(rd());
	std::uniform_int_distribution<uintmax_t>	dist;
	std::list<victoire_stone>	result;
	std::vector<position>	pos;
	victoire_stone vic;

	utils(board, pos);
	for (position &i : pos)
	{
		vic.score = 0;
		for (uintmax_t k = 0; k < n; k++)
		{
			Board	cpy_board(board);
			std::vector<position> cpy_pos(pos);
			utils(cpy_board, cpy_pos, i);
			if (play(cpy_board, cpy_pos, gen, dist) == board.get_turn())
				vic.score++;
		}
		vic.x = i.x;
		vic.y = i.y;
		result.push_back(vic);
	}
	for (victoire_stone &i : result)
	{
		if (vic.score < i.score)
			vic = i;
		std::cout << i.score << std::endl;
	}
	stone_final.color = board.get_turn();
	stone_final.x = vic.x;
	stone_final.y = vic.y;
}

iprotocol::Game_stone::Color	AI::play(Board &board, std::vector<position> &pos, std::default_random_engine &gen, std::uniform_int_distribution<uintmax_t> &dist)
{
	iprotocol::Game_stone::Color	col;
	while ((col = Arbitre::check_victory(board, false, true)) == iprotocol::Game_stone::None && pos.size() != 0)
	{
		uintmax_t choix = dist(gen) % pos.size();
		position i;
		i.x = pos[choix].x;
		i.y = pos[choix].y;
		utils(board, pos, i);
	}
	return col;
}

/*
void	AI::play(Board const &board, iprotocol::Game_stone &stone_final, uintmax_t n)
{
	iprotocol::Game_stone stone;
	stone.color = board.get_turn();
	intmax_t	max_value = INTMAX_MIN;
	for (uint8_t i = 0; i < Board::size; i++)
	{
		stone.x = i;
		for (uint8_t j = 0; j < Board::size; j++)
		{
			if (Arbitre::can_put_stone(&stone, board, false))
			{
				Board cpy_board = board;
				stone.y = j;
				std::vector<iprotocol::Game_stone *>	useless;
				cpy_board.put_stone(stone.x, stone.y, stone.color, useless);
				intmax_t value = min(board, cpy_board, stone.color, n);
				if (value > max_value)
				{
					max_value = value;
					stone_final = stone;
				}
			}
			std::cout << (int)i << " " << (int)j << std::endl;
		}
	}
}

intmax_t	AI::min(Board const &board_ai, Board const &board, iprotocol::Game_stone::Color color_ai, uintmax_t n)
{
	if (n == 0 || Arbitre::check_victory(board, false, true) != Square::col::None)
		return eval(board_ai, board, color_ai);
	iprotocol::Game_stone stone;
	stone.color = board.get_turn();
	intmax_t	min_value = INTMAX_MAX;
	for (uint8_t i = 0; i < Board::size; i++)
	{
		stone.x = i;
		for (uint8_t j = 0; j < Board::size; j++)
		{
			if (Arbitre::can_put_stone(&stone, board, false))
			{
				Board cpy_board = board;
				stone.y = j;
				std::vector<iprotocol::Game_stone *>	useless;
				cpy_board.put_stone(stone.x, stone.y, stone.color, useless);
				intmax_t value = max(board_ai, cpy_board, color_ai, n - 1);
				if (value < min_value)
					min_value = value;
			}
		}
	}
	return min_value;
}

intmax_t	AI::max(Board const &board_ai, Board const &board, iprotocol::Game_stone::Color color_ai, uintmax_t n)
{
	if (n == 0 || Arbitre::check_victory(board, false, true) != Square::col::None)
		return eval(board_ai, board, color_ai);
	iprotocol::Game_stone stone;
	stone.color = board.get_turn();
	intmax_t	max_value = INTMAX_MIN;
	for (uint8_t i = 0; i < Board::size; i++)
	{
		stone.x = i;
		for (uint8_t j = 0; j < Board::size; j++)
		{
			if (Arbitre::can_put_stone(&stone, board, false))
			{
				Board cpy_board = board;
				stone.y = j;
				std::vector<iprotocol::Game_stone *>	useless;
				cpy_board.put_stone(stone.x, stone.y, stone.color, useless);
				intmax_t value = min(board_ai, cpy_board, color_ai, n - 1);
				if (value < max_value)
					max_value = value;
			}
		}
	}
	return max_value;
}

static uintmax_t	je_compte(Board const &board, iprotocol::Game_stone::Color color)
{
	uintmax_t	score = 0;
	for (uint8_t i = 0; i < Board::size; i++)
	{
		for (uint8_t j = 0; j < Board::size; j++)
		{
		Square	const &square = board.get_square(i, j);
		if (square.get_color() == color)
			{
				std::vector<Square::Combi>	const &combis = square.get_combis();
				for (Square::Combi const &combi : combis)
				{
					int coef = 5;
					if (combi.isOpenDown())
						coef += 2;
					if (combi.isOpenUp())
						coef += 2;
					if (combi.isBroken())
						coef = -2;
					score += coef * combi.getSize();
				}
			}
		}
	}
	return (score);
}

intmax_t	AI::eval(Board const &board_ai, Board const &board, iprotocol::Game_stone::Color color_ai)
{
	iprotocol::Game_stone::Color winner = Arbitre::check_victory(board, false, true);
	if (winner == color_ai)
		return (INTMAX_MAX - 1);
	else if (winner == !color_ai)
		return (INTMAX_MIN + 1);
	intmax_t	score = 0;
	int point_ai = board.get_point(color_ai) - board_ai.get_point(color_ai);
	int point = board.get_point(!color_ai) - board_ai.get_point(!color_ai);
	score -= 100 * point;
	score += 100 * point_ai;
	intmax_t combi_ai = je_compte(board, color_ai) - je_compte(board_ai, color_ai);
	intmax_t combi = je_compte(board, !color_ai) - je_compte(board_ai, !color_ai);
	score += combi;
	score += combi_ai;
	return (score);
}*/