#pragma once

#include <array>
#include "ACallback.hpp"
#include "ITCP_protocol.hpp"
#include "Client.hpp"

class Arbitre : public ACallback<Client>
{
public:
	Arbitre(ITCP_protocol<Client>::Callback& itcp_protocol);
	Arbitre(const Arbitre &copy);
	~Arbitre(void);

	void	put_stone_game(ITCP_protocol<Client> &itcp_protocol, ITCP_protocol<Client>::Game_stone *stone);

	bool	can_put_stone(ITCP_protocol<Client>::Game_stone *stone) const;

	bool	is_double_three(ITCP_protocol<Client>::Game_stone *stone) const;

	bool	check_three(int coord[4], ITCP_protocol<Client>::Game_stone *stone) const;

	bool	is_horizontal_three(int coord[4], ITCP_protocol<Client>::Game_stone *stone) const;

	const ITCP_protocol<Client>::Game_stone::Color& operator()(int x, int y) const;

	ITCP_protocol<Client>::Game_stone::Color& operator()(int x, int y);

	static const int board_size = 19;
private:
	std::array<ITCP_protocol<Client>::Game_stone::Color, board_size * board_size>	m_board;
	int			m_white_loose;
	int			m_black_loose;
	bool		m_is_black_turn;
};