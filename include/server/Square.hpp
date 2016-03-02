#pragma once

#include	<vector>
#include	<utility>
#include	"Client.hpp"
#include	"ITCP_protocol.hpp"

class Board;

class Square
{
public:
	typedef std::pair<int, int>	pos;
	typedef iprotocol::Game_stone::Color	col;

	class Combi /* De ski */
	{
	public:
		Combi(pos begin, pos end, const Board &board);
		Combi(pos begin, pos end, const Board &board, std::pair<int, int> coeff);
		Combi(Combi const &other);
		~Combi();

		Combi	operator=(const Combi &other);
		bool operator==(const Combi &other) const;
		bool operator!=(const Combi &other) const;

		bool check_validity(const Board & b) const;

		std::pair<int, int> getCoeff() const;

		bool isInclude(Combi newCombi);
		const pos	&getBegin() const;
		const pos	&getEnd() const;
		int		getSize() const;
		bool	isBroken() const;
		bool	isOpenUp() const;
		bool	isOpenDown() const;
		col		getSide() const;
		int get_index(pos p);
	private:
		pos		m_begin;
		pos		m_end;
		int		m_size;
		bool	m_isBroken;
		bool	m_isOpenUp;
		bool	m_isOpenDown;
		std::pair<int, int> m_coeff;
		col		m_side;
	};

	Square(const pos &pos);
	Square(const Square &copy);
	~Square();

	Square	operator=(const Square &copy) = delete;
	bool	operator==(const Square &other) const;
	bool	operator!=(const Square &other) const;
	bool	operator==(pos &other) const;
	bool	operator!=(pos &other) const;
	void	put_stone(col new_color);
	void	update(const Combi &newCombi);
	void update(Board & b);
	void delete_line(std::pair<int, int> coeff, Board &b);
	void delete_combi(const Combi &combi);
	col		get_color() const;
	pos		get_pos() const;
	const std::vector<Combi>	&get_combis() const;
private:
	pos		m_pos;
	col		m_col;
	std::vector<Combi> m_combis;
};

