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
	if (stone->x >= 19)
		return false;
	if (stone->y >= 19)
		return false;
	if ((*this)(stone->x, stone->y) != prot::Game_stone::Color::None)
		return (false);
	if (is_double_three(stone))
		return false;
	return true;
}

bool Arbitre::is_horizontal_three(int coord[4], ITCP_protocol<Client>::Game_stone * stone) const
{
	int		i = 1;
	int		x = static_cast<int>(stone->x);
	int		tmp = 0;
	int		nb[3] = { 0, 0, 0 };
	bool	empty = true;

	while ((empty || (*this)(x + i, stone->y) != prot::Game_stone::Color::None) && x + i < Arbitre::board_size)
	{
		if (prot::Game_stone::notColor((*this)(x + i, stone->y)) == stone->color)
			break;
		if ((*this)(x + i, stone->y) == prot::Game_stone::Color::None)
		{
			coord[0] = x + i - 1;
			coord[1] = stone->y;
			nb[1] += i;
			empty = false;
		}
		else if (empty == false)
			tmp++;
		i++;
	}
	nb[2] = tmp;
	i = 1;
	tmp = 0;
	empty = true;
	while ((empty || (*this)(x - i, stone->y) != prot::Game_stone::Color::None) && x - i > -1)
	{
		if (prot::Game_stone::notColor((*this)(x - i, stone->y)) == stone->color)
			break;
		if ((*this)(x - i, stone->y) == prot::Game_stone::Color::None)
		{
			coord[2] = x - i + 1;
			coord[3] = stone->y;
			nb[1] += i - 1;
			empty = false;
		}
		else if (empty == false)
			tmp++;
		i++;
	}
	nb[0] = tmp;
	if (nb[1] == 3);
	else if (nb[1] + nb[0] == 3)
	{
		coord[2] = coord[0] - 4;
	}
	else if (nb[1] + nb[2] == 3)
	{
		coord[0] = coord[2] + 4;
	}
	else
		return false;
	return true;
}

bool Arbitre::is_vertical_three(int coord[4], ITCP_protocol<Client>::Game_stone * stone) const
{
	int		i = 1;
	int		y = static_cast<int>(stone->y);
	int		tmp = 0;
	int		nb[3] = { 0, 0, 0 };
	bool	empty = true;

	while ((empty || (*this)(stone->x, y + i) != prot::Game_stone::Color::None) && y + i < Arbitre::board_size)
	{
		if (prot::Game_stone::notColor((*this)(stone->x, y + i)) == stone->color)
			break;
		if ((*this)(stone->x, y + i) == prot::Game_stone::Color::None)
		{
			coord[0] = stone->x;
			coord[1] = y + i - 1;
			nb[1] += i;
			empty = false;
		}
		else if (empty == false)
			tmp++;
		i++;
	}
	nb[2] = tmp;
	i = 1;
	tmp = 0;
	empty = true;
	while ((empty || (*this)(stone->x, y - i) != prot::Game_stone::Color::None) && y - i > -1)
	{
		if (prot::Game_stone::notColor((*this)(stone->x, y - i)) == stone->color)
			break;
		if ((*this)(stone->x, y - i) == prot::Game_stone::Color::None)
		{
			coord[2] = stone->x;
			coord[3] = y - i + 1;
			nb[1] += i - 1;
			empty = false;
		}
		if (empty == false)
			tmp++;
		i++;
	}
	nb[0] = tmp;
	if (nb[1] == 3);
	else if (nb[1] + nb[0] == 3)
	{
		coord[3] = coord[1] - 4;
	}
	else if (nb[1] + nb[2] == 3)
	{
		coord[1] = coord[3] + 4;
	}
	else
		return false;
	return true;
}

bool Arbitre::is_diag_iso_three(int coord[4], ITCP_protocol<Client>::Game_stone * stone) const
{
	int		i = 1;
	int		x = static_cast<int>(stone->x);
	int		y = static_cast<int>(stone->y);
	int		tmp = 0;
	int		nb[3] = { 0, 0, 0 };
	bool	empty = true;

	while ((empty || (*this)(x + i, y + i) != prot::Game_stone::Color::None) && x + i < Arbitre::board_size && y + i < Arbitre::board_size)
	{
		if (prot::Game_stone::notColor((*this)(x + i, y + i)) == stone->color)
			break;
		if ((*this)(x + i, y + i) == prot::Game_stone::Color::None)
		{
			coord[0] = x + i - 1;
			coord[1] = y + i - 1;
			nb[1] += i;
			empty = false;
		}
		else if (empty == false)
			tmp++;
		i++;
	}
	nb[2] = tmp;
	i = 1;
	tmp = 0;
	empty = true;
	while ((empty || (*this)(x - i, y - i) != prot::Game_stone::Color::None) && x - i > -1 && y - i > -1)
	{
		if (prot::Game_stone::notColor((*this)(x - i, y - i)) == stone->color)
			break;
		if ((*this)(x - i, y - i) == prot::Game_stone::Color::None)
		{
			coord[2] = x - i + 1;
			coord[3] = y - i + 1;
			nb[1] += i - 1;
			empty = false;
		}
		else if (empty == false)
			tmp++;
		i++;
	}
	nb[0] = tmp;
	if (nb[1] == 3);
	else if (nb[1] + nb[0] == 3)
	{
		coord[2] = coord[0] - 4;
		coord[3] = coord[1] - 4;
	}
	else if (nb[1] + nb[2] == 3)
	{
		coord[0] = coord[2] + 4;
		coord[1] = coord[3] + 4;
	}
	else
		return false;
	return true;
}

bool Arbitre::is_diag_no_iso_three(int coord[4], ITCP_protocol<Client>::Game_stone * stone) const
{
	int		i = 1;
	int		x = static_cast<int>(stone->x);
	int		y = static_cast<int>(stone->y);
	int		tmp = 0;
	int		nb[3] = { 0, 0, 0 };
	bool	empty = true;

	while ((empty || (*this)(x - i, y + i) != prot::Game_stone::Color::None) && x - i > 0 && y + i < Arbitre::board_size)
	{
		if (prot::Game_stone::notColor((*this)(x - i, y + i)) == stone->color)
			break;
		if ((*this)(x - i, y + i) == prot::Game_stone::Color::None)
		{
			coord[0] = x - i + 1;
			coord[1] = y + i - 1;
			nb[1] += i;
			empty = false;
		}
		else if (empty == false)
			tmp++;
		i++;
	}
	nb[2] = tmp;
	i = 1;
	tmp = 0;
	empty = true;
	while ((empty || (*this)(x + i, y - i) != prot::Game_stone::Color::None) && x + i < Arbitre::board_size && y - i > -1)
	{
		if (prot::Game_stone::notColor((*this)(x + i, y - i)) == stone->color)
			break;
		if ((*this)(x + i, y - i) == prot::Game_stone::Color::None)
		{
			coord[2] = x + i - 1;
			coord[3] = y - i + 1;
			nb[1] += i - 1;
			empty = false;
		}
		else if (empty == false)
			tmp++;
		i++;
	}
	nb[0] = tmp;
	if (nb[1] == 3);
	else if (nb[1] + nb[0] == 3)
	{
		coord[3] = coord[1] - 4;
		coord[2] = coord[0] + 4;
	}
	else if (nb[1] + nb[2] == 3)
	{
		coord[3] = coord[1] + 4;
		coord[0] = coord[2] - 4;
	}
	else
		return false;
	return true;
}

bool Arbitre::check_horizontal_three(int coord[4], ITCP_protocol<Client>::Game_stone * stone) const
{
	int x;
	int tmp[4] = { -1, -1, -1, -1 };

	x = coord[0];
	while (x <= coord[2])
	{
		if ((*this)(x, coord[1]) == stone->color || x == stone->x)
		{
			if (is_vertical_three(tmp, stone))
				return true;
			if (is_diag_iso_three(tmp, stone))
				return true;
			if (is_diag_no_iso_three(tmp, stone))
				return true;
		}
		x++;
	}
	return false;
}

bool Arbitre::check_vertical_three(int coord[4], ITCP_protocol<Client>::Game_stone * stone) const
{
	int y;
	int tmp[4] = { -1, -1, -1, -1 };

	y = coord[1];
	while (y <= coord[3])
	{
		if ((*this)(coord[0], y) == stone->color || y == stone->y)
		{
			if (is_horizontal_three(tmp, stone))
				return true;
			if (is_diag_iso_three(tmp, stone))
				return true;
			if (is_diag_no_iso_three(tmp, stone))
				return true;
		}
		y++;
	}
	return false;
}

bool Arbitre::check_diag_iso_three(int coord[4], ITCP_protocol<Client>::Game_stone * stone) const
{
	int x;
	int y;
	int tmp[4] = { -1, -1, -1, -1 };

	x = coord[1];
	y = coord[1];
	while (y <= coord[3])
	{
		if ((*this)(x, y) == stone->color || y == stone->y)
		{
			if (is_vertical_three(tmp, stone))
				return true;
			if (is_horizontal_three(tmp, stone))
				return true;
			if (is_diag_no_iso_three(tmp, stone))
				return true;
		}
		x++;
		y++;
	}
	return false;
}

bool Arbitre::check_diag_no_iso_three(int coord[4], ITCP_protocol<Client>::Game_stone * stone) const
{
	int x;
	int y;
	int tmp[4] = { -1, -1, -1, -1 };

	x = coord[1];
	y = coord[1];
	while (y <= coord[3])
	{
		if ((*this)(x, y) == stone->color || y == stone->y)
		{
			if (is_vertical_three(tmp, stone))
				return true;
			if (is_horizontal_three(tmp, stone))
				return true;
			if (is_diag_iso_three(tmp, stone))
				return true;
		}
		x--;
		y++;
	}
	return false;
}

bool Arbitre::is_double_three(ITCP_protocol<Client>::Game_stone * stone) const
{
	int coord[4] = { -1, -1, -1, -1 };

	if (is_horizontal_three(coord, stone))
		return check_horizontal_three(coord, stone);
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
