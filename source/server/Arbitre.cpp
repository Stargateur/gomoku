#include "Arbitre.hpp"

using prot = ITCP_protocol<Client>;

Arbitre::Arbitre(ITCP_protocol<Client>::Callback &itcp_protocol) :
	ACallback(itcp_protocol),
	m_board(),
	m_white_loose(0),
	m_black_loose(0),
	m_is_black_turn(true)
{
	for (int i = 0; i < Arbitre::board_size; i++)
	{
		for (int j = 0; j < Arbitre::board_size; j++)
		{
			m_board[i * Arbitre::board_size + j] = prot::Game_stone::Color::None;
		}
	}
}

Arbitre::Arbitre(const Arbitre & copy) :
	ACallback(copy),
	m_board(copy.m_board),
	m_white_loose(0),
	m_black_loose(0),
	m_is_black_turn(copy.m_is_black_turn)
{}

Arbitre::~Arbitre(void)
{}

void Arbitre::put_stone_game(ITCP_protocol<Client> &itcp_protocol, prot::Game_stone * stone)
{
	if (can_put_stone(stone))
		itcp_protocol.send_game_stone_put(*stone);
	//Verif Capture + victoire
}

bool Arbitre::can_put_stone(ITCP_protocol<Client>::Game_stone * stone) const
{
	if (m_is_black_turn && stone->color != prot::Game_stone::Color::Black)
		return false;
	if (!m_is_black_turn && stone->color != prot::Game_stone::Color::White)
		return false;
	if (stone->x < 0 || stone->x >= 19)
		return false;
	if (stone->y < 0 || stone->y >= 19)
		return false;
	if ((*this)(stone->x, stone->y) != prot::Game_stone::Color::None)
		return (false);
	if (is_double_three(stone))
		return false;
	return true;
}

bool Arbitre::is_horizontal_three(int coord[4], ITCP_protocol<Client>::Game_stone * stone) const
{
	return false;
}

bool Arbitre::check_three(int coord[4], ITCP_protocol<Client>::Game_stone * stone) const
{
	return false;

}

bool Arbitre::is_double_three(ITCP_protocol<Client>::Game_stone * stone) const
{
	int coord[4] = { -1, -1, -1, -1 };

	if (is_horizontal_three(coord, stone))
		return check_three(coord, stone);
	return false;
}

const ITCP_protocol<Client>::Game_stone::Color & Arbitre::operator()(int x, int y) const
{
	return (m_board[x * Arbitre::board_size + y]);
}

ITCP_protocol<Client>::Game_stone::Color & Arbitre::operator()(int x, int y)
{
	return (m_board[x * Arbitre::board_size + y]);
}
