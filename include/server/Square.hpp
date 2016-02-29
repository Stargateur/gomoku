#pragma once

#include	<vector>
#include	<utility>
#include	"Client.hpp"
#include	"ITCP_protocol.hpp"

class Square
{
public:
	typedef std::pair<int, int>	pos;
	typedef	ITCP_protocol<Client>::Game_stone::Color	col;

	class Combi /* De ski */
	{
	public:
	};

	Square(const pos &pos);
	Square(const Square &copy);
	~Square();

	Square	operator=(const Square &copy);
	bool	operator==(const Square &other) const;
	bool	operator!=(const Square &other) const;
	bool	operator==(pos &other) const;
	bool	operator!=(pos &other) const;
	void	put_stone(col new_color);
	void	update(std::vector<Combi> combis);
	col		get_color() const;
	pos		get_pos() const;
	std::vector<Combi>	get_combis() const;
private:
	pos		m_pos;
	col		m_col;
	std::vector<Combi> m_combis;
};

