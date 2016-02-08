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

bool Arbitre::check_coord(int x, int y) const
{
	if (x < 0 || x >= Arbitre::board_size)
		return false;
	if (y < 0 || y >= Arbitre::board_size)
		return false;
	return true;
}

bool Arbitre::check_stone_libre(int x, int y) const
{
	int tab[8][2] = {
		{ 1, 0 },
		{ 0, 1 },
		{ -1, 0 },
		{ 0, -1 },
		{ 1, 1 },
		{ -1, -1 },
		{ 1, -1 },
		{ -1, 1 }
	};

	for (int i = 0; i < 8; i++)
	{
		if (check_coord(x + tab[i][0], y + tab[i][1]) == false)
			continue;
		if ((*this)(x + tab[i][0], y + tab[i][1]) != prot::Game_stone::Color::None)
			continue;
		if (check_coord(x - tab[i][0], y - tab[i][1]) == false)
			continue;
		if ((*this)(x + tab[i][0], y + tab[i][1]) != (*this)(x, y))
			continue;
		if (check_coord(x - tab[i][0] * 2, y - tab[i][1] * 2) == false)
			continue;
		if ((*this)(x + tab[i][0], y + tab[i][1]) != prot::Game_stone::notColor((*this)(x, y)))
			continue;
		return (false);
	}
	return (true);
}

void Arbitre::check_vertical_victory(prot::Game_stone *stone) const
{
	int tab[4][2] =
	{
		{ 0, 1 },
		{ 1, 0 },
		{ 1, 1 },
		{ 1, -1 },
	};
	int i = 0;
	int j = 0;
	int	nb = 0;
	int x = static_cast<int>(stone->x);
	int y = static_cast<int>(stone->y);
	for (int k = 0; k < 4; k++)
	{
		while (check_coord(x + i, y + j) && (*this)(x + i, y + j) == stone->color)
		{
			if (check_stone_libre(x + i, y + j) == false)
				break;
			i += tab[k][0];
			j += tab[k][1];
			nb++;
		}
		i = tab[k][0];
		j = tab[k][1];
		while (check_coord(x - i, y - j) > 0 && (*this)(x - i, y - j) == stone->color)
		{
			if (check_stone_libre(x - i, y) == false)
				break;
			i += tab[k][0];
			j += tab[k][1];
			nb++;
		}
		if (nb >= 5)
			throw std::logic_error("La game est finie.");
	}
}

void Arbitre::check_victory(prot::Game_stone * stone) const
{
	if (m_black_loose >= 10)
		throw std::logic_error("La game est finie. Blanc a gagne");
	if (m_white_loose >= 10)
		throw std::logic_error("La game est finie. Noir a gagne");
	check_vertical_victory(stone);
}

void Arbitre::put_stone_game(ITCP_protocol<Client> &itcp_protocol, prot::Game_stone * stone)
{
	int capture[8][4] = {
		{ -1, -1, -1, -1 },
		{ -1, -1, -1, -1 },
		{ -1, -1, -1, -1 },
		{ -1, -1, -1, -1 },
		{ -1, -1, -1, -1 },
		{ -1, -1, -1, -1 },
		{ -1, -1, -1, -1 },
		{ -1, -1, -1, -1 }
	};

	if (can_put_stone(stone))
	{
		itcp_protocol.send_game_stone_put(*stone);
		(*this)(stone->x, stone->y) = stone->color;
	}
	if (can_capture(stone, capture))
	{
		prot::Game_stone mess;
		mess.color = prot::Game_stone::Color::None;
		int i = 0;
		while (capture[i][0] != -1)
		{
			mess.x = capture[i][0];
			mess.y = capture[i][1];
			itcp_protocol.send_game_stone_put(mess);
			(*this)(stone->x, stone->y) = prot::Game_stone::Color::None;
			mess.x = capture[i][2];
			mess.y = capture[i][3];
			itcp_protocol.send_game_stone_put(mess);
			(*this)(stone->x, stone->y) = prot::Game_stone::Color::None;
			if (stone->color = prot::Game_stone::Color::Black)
				m_white_loose += 2;
			else
				m_black_loose += 2;
			i++;
		}
	}
	check_victory(stone);
}

bool Arbitre::can_capture(prot::Game_stone * stone, int coord[8][4]) const
{
	int x = stone->x;
	int y = stone->y;
	int i = 0;

	if (x - 3 > -1 && (*this)(x - 3, y) == stone->color)
	{
		if ((*this)(x - 2, y) == prot::Game_stone::notColor(stone->color) && (*this)(x - 1, y) == prot::Game_stone::notColor(stone->color))
		{
			coord[i][0] = x - 2;
			coord[i][1] = y;
			coord[i][2] = x - 1;
			coord[i][3] = y;
			i++;
		}
	}
	if (x + 3 < Arbitre::board_size && (*this)(x + 3, y) == stone->color)
	{
		if ((*this)(x + 2, y) == prot::Game_stone::notColor(stone->color) && (*this)(x + 1, y) == prot::Game_stone::notColor(stone->color))
		{
			coord[i][0] = x + 2;
			coord[i][1] = y;
			coord[i][2] = x + 1;
			coord[i][3] = y;
			i++;
		}
	}
	if (y - 3 > -1 && (*this)(x, y - 3) == stone->color)
	{
		if ((*this)(x, y - 2) == prot::Game_stone::notColor(stone->color) && (*this)(x, y - 1) == prot::Game_stone::notColor(stone->color))
		{
			coord[i][0] = x;
			coord[i][1] = y - 2;
			coord[i][2] = x;
			coord[i][3] = y - 1;
			i++;
		}
	}
	if (y + 3 < Arbitre::board_size && (*this)(x, y + 3) == stone->color)
	{
		if ((*this)(x, y + 2) == prot::Game_stone::notColor(stone->color) && (*this)(x, y + 1) == prot::Game_stone::notColor(stone->color))
		{
			coord[i][0] = x;
			coord[i][1] = y + 2;
			coord[i][2] = x;
			coord[i][3] = y + 1;
			i++;
		}
	}
	if (x - 3 > -1 && y - 3 > -1 && (*this)(x - 3, y - 3) == stone->color)
	{
		if ((*this)(x - 2, y - 2) == prot::Game_stone::notColor(stone->color) && (*this)(x - 1, y - 1) == prot::Game_stone::notColor(stone->color))
		{
			coord[i][0] = x - 2;
			coord[i][1] = y - 2;
			coord[i][2] = x - 1;
			coord[i][3] = y - 1;
			i++;
		}
	}
	if (x + 3 < Arbitre::board_size && y + 3 < Arbitre::board_size && (*this)(x + 3, y + 3) == stone->color)
	{
		if ((*this)(x + 2, y + 2) == prot::Game_stone::notColor(stone->color) && (*this)(x + 1, y + 1) == prot::Game_stone::notColor(stone->color))
		{
			coord[i][0] = x + 2;
			coord[i][1] = y + 2;
			coord[i][2] = x + 1;
			coord[i][3] = y + 1;
			i++;
		}
	}
	if (x + 3 > -1 && y - 3 > -1 && (*this)(x + 3, y - 3) == stone->color)
	{
		if ((*this)(x + 2, y - 2) == prot::Game_stone::notColor(stone->color) && (*this)(x + 1, y - 1) == prot::Game_stone::notColor(stone->color))
		{
			coord[i][0] = x + 2;
			coord[i][1] = y - 2;
			coord[i][2] = x + 1;
			coord[i][3] = y - 1;
			i++;
		}
	}
	if (x - 3 < Arbitre::board_size && y + 3 < Arbitre::board_size && (*this)(x - 3, y + 3) == stone->color)
	{
		if ((*this)(x - 2, y + 2) == prot::Game_stone::notColor(stone->color) && (*this)(x - 1, y + 1) == prot::Game_stone::notColor(stone->color))
		{
			coord[i][0] = x - 2;
			coord[i][1] = y + 2;
			coord[i][2] = x - 1;
			coord[i][3] = y + 1;
			i++;
		}
	}
	return (i != 0);
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

	while (x + i < Arbitre::board_size && (empty || (*this)(x + i, stone->y) != prot::Game_stone::Color::None))
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
	while (x - i > -1 && (empty || (*this)(x - i, stone->y) != prot::Game_stone::Color::None))
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

	while (y + i < Arbitre::board_size && (empty || (*this)(stone->x, y + i) != prot::Game_stone::Color::None))
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
	while (y - i > -1 && (empty || (*this)(stone->x, y - i) != prot::Game_stone::Color::None))
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

	while (x + i < Arbitre::board_size && y + i < Arbitre::board_size && (empty || (*this)(x + i, y + i) != prot::Game_stone::Color::None))
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
	while (x - i > -1 && y - i > -1 && (empty || (*this)(x - i, y - i) != prot::Game_stone::Color::None))
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

	while (x - i > 0 && y + i < Arbitre::board_size && (empty || (*this)(x - i, y + i) != prot::Game_stone::Color::None))
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
	while (x + i < Arbitre::board_size && y - i > -1 && (empty || (*this)(x + i, y - i) != prot::Game_stone::Color::None))
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
