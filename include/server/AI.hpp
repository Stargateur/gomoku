#ifndef		AI_HPP_
# define	AI_HPP_

# include	<random>
# include	"ITCP_protocol.hpp"
# include	"Board.hpp"

class AI
{
public:
	struct victoire_stone
	{
		uint8_t	x;
		uint8_t	y;
		uintmax_t	score;
	};
	struct position
	{
		uint8_t	x;
		uint8_t	y;
	};
	static void	play(Board const &board, iprotocol::Game_stone &stone_final, uintmax_t n);
	static void	utils(Board const &board, std::vector<position> &pos, int &nb_stone);
	static void	utils(Board &board, std::vector<position> &pos, position const &i);
	static iprotocol::Game_stone::Color	play(Board &board, std::vector<position> &pos, std::default_random_engine &gen, std::uniform_int_distribution<uintmax_t> &dist);
	/*
public:
static void	play(Board const &board, iprotocol::Game_stone &stone_final, uintmax_t n);
private:
	static intmax_t	min(Board const &board_ai, Board const &board, iprotocol::Game_stone::Color color_ai, uintmax_t n);
	static intmax_t	max(Board const &board_ai, Board const &board, iprotocol::Game_stone::Color color_ai, uintmax_t n);
	static intmax_t	eval(Board const &board_ai, Board const &board, iprotocol::Game_stone::Color color_ai);*/
};

#endif		/* !AI_HPP_ */
