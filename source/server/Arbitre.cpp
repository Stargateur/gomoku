#include <iostream>
#include "Arbitre.hpp"

using prot = ITCP_protocol<Client>;

#pragma region Log

Arbitre::log_level::log_level(Arbitre::log_level::log l) :
	m_l(l)
{}

Arbitre::log_level::log_level(const log_level & copy) :
	m_l(copy.get_log())
{
}

Arbitre::log_level Arbitre::log_level::operator=(const Arbitre::log_level & copy)
{
	set_log(copy.get_log());
	return (*this);
}

bool Arbitre::log_level::operator!=(const log_level & copy) const
{
	return (get_log() != copy.get_log());
}

bool Arbitre::log_level::operator==(const log_level & copy) const
{
	return (get_log() == copy.get_log());
}

Arbitre::log_level::~log_level()
{}

void Arbitre::log_level::set_log(Arbitre::log_level::log l)
{
	m_l = l;
}

Arbitre::log_level::log Arbitre::log_level::get_log() const
{
	return (m_l);
}

Arbitre::log_level	Arbitre::log_level::operator&(const Arbitre::log_level &copy) const
{
	return (int_to_log(log_to_int(get_log()) & log_to_int(copy.get_log())));
}

Arbitre::log_level	Arbitre::log_level::operator|(const Arbitre::log_level &copy) const
{
	return (int_to_log(log_to_int(get_log()) | log_to_int(copy.get_log())));
}

int				Arbitre::log_level::log_to_int(Arbitre::log_level::log l) const
{
	switch (l)
	{
	case None:
		return (0);
	case Can_play:
		return (1);
	case Capture:
		return (2);
	case Double_three:
		return (4);
	case Victory:
		return (8);
	default:
		throw (std::logic_error("Unexpected enum"));
	}
}

Arbitre::log_level::log		Arbitre::log_level::int_to_log(int l) const
{
	switch (l)
	{
	case 0:
		return (None);
	case 1:
		return (Can_play);
	case 2:
		return (Capture);
	case 4:
		return (Double_three);
	case 8:
		return (Victory);
	}
	throw (std::logic_error("Unexpected int"));
}

#pragma endregion

#pragma region Constructeur

Arbitre::Arbitre(ITCP_protocol<Client>::Callback &itcp_protocol) :
	ACallback(itcp_protocol),
	m_board(),
	m_white_loose(0),
	m_black_loose(0),
	m_is_black_turn(true),
	m_level(log_level::Double_three)
{
	for (unsigned int i = 0; i < Arbitre::board_size; i++)
	{
		for (unsigned int j = 0; j < Arbitre::board_size; j++)
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
	m_is_black_turn(copy.m_is_black_turn),
	m_level(copy.m_level)
{}

Arbitre::~Arbitre(void)
{}

#pragma endregion

void Arbitre::dump(void) const
{
	for (int i = 0; i < Arbitre::board_size; i++)
	{
		for (int j = 0; j < Arbitre::board_size; j++)
		{
			prot::Game_stone::Color col = (*this)(i, j);
			if (col == prot::Game_stone::Color::None)
				std::cout << " ";
			if (col == prot::Game_stone::Color::Black)
				std::cout << "o";
			if (col == prot::Game_stone::Color::White)
				std::cout << "x";
		}
		std::cout << std::endl;
	}
}

void Arbitre::set_log_level(log_level l)
{
	m_level = l;
}

bool Arbitre::check_coord(int x, int y) const
{
	if (x < 0 || x >= Arbitre::board_size)
		return false;
	if (y < 0 || y >= Arbitre::board_size)
		return false;
	return true;
}

#pragma region Victory

bool Arbitre::check_stone_libre(int x, int y) const
{
	int tab[8][2] = {
		{ 1, 0 },
		{ 0, 1 },
		{-1, 0 },
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
		if (check_coord(x - tab[i][0], y - tab[i][1]) == false)
			continue;
		if (check_coord(x - tab[i][0] * 2, y - tab[i][1] * 2) == false)
			continue;
		if ((*this)(x - tab[i][0], y - tab[i][1]) != (*this)(x, y))
			continue;
		if (((*this)(x + tab[i][0], y + tab[i][1]) != prot::Game_stone::Color::None ||
				(*this)(x - tab[i][0] * 2, y - tab[i][1] * 2) != prot::Game_stone::notColor((*this)(x, y)))
			&& ((*this)(x + tab[i][0], y + tab[i][1]) != prot::Game_stone::notColor((*this)(x, y)) ||
				(*this)(x - tab[i][0] * 2, y - tab[i][1] * 2) != prot::Game_stone::Color::None))
			continue;
		return (false);
	}
	return (true);
}

void Arbitre::check_victory_five(ITCP_protocol<Client> &itcp_protocol, prot::Game_stone *stone)
{
	int tab[4][2] =
	{
		{ 0, 1 },
		{ 1, 0 },
		{ 1, 1 },
		{ 1, -1 }
	};
	for (int x = 0; x < Arbitre::board_size; x++)
	{
		for (int y = 0; y < Arbitre::board_size; y++)
		{
			if ((*this)(x, y) == stone->color)
			{
				for (int k = 0; k < 4; k++)
				{
					int nb = 0;
					int i = 0;
					int j = 0;
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
					while (check_coord(x - i, y - j) && (*this)(x - i, y - j) == stone->color)
					{
						if (check_stone_libre(x - i, y - j) == false)
							break;
						i += tab[k][0];
						j += tab[k][1];
						nb++;
					}
					if (nb >= 5)
					{
						prot::Game_result gr;
						gr.winner = new std::string("Fin de la game");
						m_callback.result_game(itcp_protocol, &gr);
					}
				}
			}
		}
	}
}

void Arbitre::check_victory(ITCP_protocol<Client> &itcp_protocol, prot::Game_stone * stone)
{
	if (m_black_loose >= 10)
	{
		prot::Game_result gr;
		gr.winner = new std::string("Fin de la game");
		m_callback.result_game(itcp_protocol, &gr);
	}
	if (m_white_loose >= 10)
	{
		prot::Game_result gr;
		gr.winner = new std::string("Fin de la game");
		m_callback.result_game(itcp_protocol, &gr);
	}
	check_victory_five(itcp_protocol, stone);
}

#pragma endregion

#pragma region put_stone

void Arbitre::put_stone_game(ITCP_protocol<Client> &itcp_protocol, prot::Game_stone * stone)
{
	uint8_t capture[8][4] = {
		{ Arbitre::board_size, Arbitre::board_size, Arbitre::board_size, Arbitre::board_size },
		{ Arbitre::board_size, Arbitre::board_size, Arbitre::board_size, Arbitre::board_size },
		{ Arbitre::board_size, Arbitre::board_size, Arbitre::board_size, Arbitre::board_size },
		{ Arbitre::board_size, Arbitre::board_size, Arbitre::board_size, Arbitre::board_size },
		{ Arbitre::board_size, Arbitre::board_size, Arbitre::board_size, Arbitre::board_size },
		{ Arbitre::board_size, Arbitre::board_size, Arbitre::board_size, Arbitre::board_size },
		{ Arbitre::board_size, Arbitre::board_size, Arbitre::board_size, Arbitre::board_size },
		{ Arbitre::board_size, Arbitre::board_size, Arbitre::board_size, Arbitre::board_size }
	};

	if (can_put_stone(stone))
	{
		if ((m_level & log_level::Can_play) == log_level::Can_play)
			std::cout << "can put_stone (DEBUG : illo)" << std::endl;
		m_callback.put_stone_game(itcp_protocol, stone);
		(*this)(stone->x, stone->y) = stone->color;
		m_is_black_turn = !m_is_black_turn;
		if (can_capture(stone, capture))
		{
			int i = 0;
			prot::Game_stone *mess = new prot::Game_stone();
			mess->color = prot::Game_stone::Color::None;
			while (i < 8 && capture[i][0] != Arbitre::board_size)
			{
				mess->x = static_cast<unsigned char>(capture[i][0]);
				mess->y = static_cast<unsigned char>(capture[i][1]);
				m_callback.put_stone_game(itcp_protocol, mess);
				(*this)(capture[i][0], capture[i][1]) = prot::Game_stone::Color::None;
				mess->x = static_cast<unsigned char>(capture[i][2]);
				mess->y = static_cast<unsigned char>(capture[i][3]);
				m_callback.put_stone_game(itcp_protocol, mess);
				(*this)(capture[i][2], capture[i][3]) = prot::Game_stone::Color::None;
				if (stone->color == prot::Game_stone::Color::Black)
					m_white_loose += 2;
				else
					m_black_loose += 2;
				i++;
				if ((m_level & log_level::Capture) == log_level::Capture)
				{
					std::cout << "white loose : " << m_white_loose << " (DEBUG : illo)" << std::endl;
					std::cout << "black loose : " << m_black_loose << " (DEBUG : illo)" << std::endl;
				}
			}
		}
		check_victory(itcp_protocol, stone);
	}
	else
		if ((m_level & log_level::Can_play) == log_level::Can_play)
			std::cout << "can not put_stone (DEBUG : illo)" << std::endl;

}

#pragma endregion

#pragma region Capture

bool Arbitre::can_capture(prot::Game_stone * stone, uint8_t coord[8][4]) const
{
	int tab[8][2] =
	{
		{ 0, 1 },
		{ 1, 1 },
		{ 1, 0 },
		{ -1, 0 },
		{ -1, -1 },
		{ 0, -1 },
		{ -1, 1 },
		{ 1, -1 }
	};
	int i = 0;

	for (int k = 0; k < 8; k++)
	{
		if (check_coord(stone->x + tab[k][0] * 3, stone->y + tab[k][1] * 3) && (*this)(stone->x + tab[k][0] * 3, stone->y + tab[k][1] * 3) == stone->color)
		{
			if ((*this)(stone->x + tab[k][0] * 2, stone->y + tab[k][1] * 2) == prot::Game_stone::notColor(stone->color) && (*this)(stone->x + tab[k][0], stone->y + tab[k][1]) == prot::Game_stone::notColor(stone->color))
			{
				if ((m_level & log_level::Capture) == log_level::Capture)
					std::cout << "capture between " << stone->x << " " << stone->y << " and " << stone->x + tab[k][0] * 3 << " " << stone->y + tab[k][1] * 3 << " (DEBUG : illo)" << std::endl;
				coord[i][0] = stone->x + tab[k][0] * 2;
				coord[i][1] = stone->y + tab[k][1] * 2;
				coord[i][2] = stone->x + tab[k][0];
				coord[i][3] = stone->y + tab[k][1];
				i++;
			}
		}
	}
	return (i != 0);
}

#pragma endregion

#pragma region Can_play


bool Arbitre::can_put_stone(ITCP_protocol<Client>::Game_stone * stone) const
{
	if (m_is_black_turn && stone->color != prot::Game_stone::Color::Black)
	{
		if ((m_level & log_level::Can_play) == log_level::Can_play)
			std::cout << "can not put_stone not your turn (DEBUG : illo)" << std::endl;
		return false;
	}
	if (!m_is_black_turn && stone->color != prot::Game_stone::Color::White)
	{
		if ((m_level & log_level::Can_play) == log_level::Can_play)
			std::cout << "can not put_stone not your turn (DEBUG : illo)" << std::endl;
		return false;
	}
	if (stone->x >= 19)
	{
		if ((m_level & log_level::Can_play) == log_level::Can_play)
			std::cout << "can not put_stone out of range (DEBUG : illo)" << std::endl;
		return false;
	}
	if (stone->y >= 19)
	{
		if ((m_level & log_level::Can_play) == log_level::Can_play)
			std::cout << "can not put_stone out of range (DEBUG : illo)" << std::endl;
		return false;
	}
	if ((*this)(stone->x, stone->y) != prot::Game_stone::Color::None)
	{
		if ((m_level & log_level::Can_play) == log_level::Can_play)
			std::cout << "can not put_stone case non libre (DEBUG : illo)" << std::endl;
		return (false);
	}
	if (is_three(stone))
	{
		if ((m_level & log_level::Can_play) == log_level::Can_play)
			std::cout << "can not put_stone double three (DEBUG : illo)" << std::endl;
		return false;
	}
	return true;
}

#pragma endregion

#pragma region Double_three

bool Arbitre::is_three_line(ITCP_protocol<Client>::Game_stone * stone, const std::pair<int, int> &coeff, std::array<std::pair<int, int>, 2> &coords) const
{
	std::array<int, 3>	tab = {0, 1, 0};
	int i = coeff.first;
	int j = coeff.second;
	bool is_broken = false;
	std::array<std::pair<int, int>, 2> empty = { std::make_pair(-1, -1), std::make_pair(-1, -1) };

	while (check_coord(stone->x + i, stone->y + j) && (is_broken == false ||  (*this)(stone->x + i, stone->y + j) == stone->color))
	{
		if ((*this)(stone->x + i, stone->y + j) == prot::Game_stone::Color::None)
		{
			is_broken = true;
			empty[0].first = stone->x + i;
			empty[0].second = stone->y + j;
		}
		else if ((*this)(stone->x + i, stone->y + j) == prot::Game_stone::notColor(stone->color))
			break;
		else
		{
			if (is_broken)
				tab[2] += 1;
			else
				tab[1] += 1;
		}
		i += coeff.first;
		j += coeff.second;
	}
	i = coeff.first;
	j = coeff.second;
	is_broken = false;
	while (check_coord(stone->x - i, stone->y - j) && (is_broken == false || (*this)(stone->x - i, stone->y - j) == stone->color))
	{
		if ((*this)(stone->x - i, stone->y - j) == prot::Game_stone::Color::None)
		{
			is_broken = true;
			empty[1].first = stone->x - i;
			empty[1].second = stone->y - j;
		}
		else if ((*this)(stone->x - i, stone->y - j) == prot::Game_stone::notColor(stone->color))
			break;
		else
		{
			if (is_broken)
				tab[0] += 1;
			else
				tab[1] += 1;
		}
		i += coeff.first;
		j += coeff.second;
	}
	if (empty[0].first == -1 || empty[1].first == -1)
		return (false);
	if (tab[1] == 3)
	{
		coords[0] = empty[1];
		coords[1] = empty[0];
		if ((m_level & log_level::Double_three) == log_level::Double_three)
			std::cout << "Find a three between " << coords[0].first << " " << coords[0].second << " and " << coords[1].first << " " << coords[1].second << " (DEBUG : illo)" << std::endl;
		return (true);
	}
	// Wow such formule
	if (tab[1] + tab[2] == 3 && (*this)(empty[0].first + (tab[2] + 1) * coeff.first, empty[0].second + (tab[2] + 1) * coeff.second) == prot::Game_stone::Color::None)
	{
		coords[0] = empty[1];
		coords[1].first = empty[0].first + (tab[2] + 1) * coeff.first;
		coords[1].second = empty[0].second + (tab[2] + 1) * coeff.second;
		if ((m_level & log_level::Double_three) == log_level::Double_three)
			std::cout << "Find a three between " << coords[0].first << " " << coords[0].second << " and " << coords[1].first << " " << coords[1].second << " (DEBUG : illo)" << std::endl;
		return (true);
	}
	if (tab[1] + tab[0] == 3 && (*this)(empty[1].first - (tab[0] + 1) * coeff.first, empty[1].second - (tab[0] + 1) * coeff.second) == prot::Game_stone::Color::None)
	{
		coords[1] = empty[0];
		coords[0].first = empty[1].first - (tab[0] + 1) * coeff.first;
		coords[0].second = empty[1].second - (tab[0] + 1) * coeff.second;
		if ((m_level & log_level::Double_three) == log_level::Double_three)
			std::cout << "Find a three between " << coords[0].first << " " << coords[0].second << " and " << coords[1].first << " " << coords[1].second << " (DEBUG : illo)" << std::endl;
		return (true);
	}
	return (false);
}

bool Arbitre::is_three(ITCP_protocol<Client>::Game_stone * stone) const
{
	std::array<std::pair<int, int>, 4> coeff =
	{
		std::make_pair(0, 1),
		std::make_pair(1, 1),
		std::make_pair(1, 0),
		std::make_pair(1, -1)
	};
	std::array<std::pair<int, int>, 2> coords;

	for (int i = 0; i < 4; i++)
	{
		if (is_three_line(stone, coeff[i], coords))
		{
			std::array<std::pair<int, int>, 2> new_coords;
			int j = coeff[i].first;
			int k = coeff[i].second;
			while (coords[0].first + j != coords[1].first || coords[0].second + k != coords[1].second)
			{
				ITCP_protocol<Client>::Game_stone new_stone;
				new_stone.x = coords[0].first + j;
				new_stone.y = coords[0].second + k;
				if (stone->x == new_stone.x && stone->y == new_stone.y)
					new_stone.color = stone->color;
				else
					new_stone.color = (*this)(new_stone.x, new_stone.y);
				if ((m_level & log_level::Double_three) == log_level::Double_three)
					std::cout << "Seeking a second three in " << static_cast<int>(new_stone.x) << " " << static_cast<int>(new_stone.y) << " (DEBUG : illo)" << std::endl;
				for (int l = 0; l < 4; l++)
				{
					if (l == i)
						continue;
					if ((stone->x == new_stone.x && stone->y == new_stone.y) || new_stone.color == stone->color)
					{
						if (is_three_line(&new_stone, coeff[l], new_coords))
							return (true);
					}
				}
				j += coeff[i].first;
				k += coeff[i].second;
			}
		}
	}
	return (false);
}
#pragma endregion

const ITCP_protocol<Client>::Game_stone::Color & Arbitre::operator()(unsigned int x, unsigned int y) const
{
	return (m_board[x * Arbitre::board_size + y]);
}

ITCP_protocol<Client>::Game_stone::Color & Arbitre::operator()(unsigned int x, unsigned int y)
{
	return (m_board[x * Arbitre::board_size + y]);
}
