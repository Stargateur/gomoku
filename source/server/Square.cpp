#include "Square.hpp"

Square::Square(const pos &pos) :
	m_pos(pos),
	m_col(col::None),
	m_combis()
{
}

Square::Square(const Square & copy) :
	m_pos(copy.m_pos),
	m_col(copy.m_col)
{
}


Square::~Square()
{
}

Square Square::operator=(const Square & copy)
{
	m_pos = copy.get_pos();
	m_col = copy.get_color();
	return *this;
}

/*
@TODO gerer les egalites de combinaisons
*/
bool Square::operator==(const Square & other) const
{
	return (get_pos() == other.get_pos() &&
		get_color() == other.get_color());
}

bool Square::operator!=(const Square & other) const
{
	return (!((*this) == other));
}

bool Square::operator==(pos & other) const
{
	return (get_pos() == other);
}

bool Square::operator!=(pos & other) const
{
	return (!((*this) == other));
}

void Square::put_stone(col new_color)
{
	m_col = new_color;
}

/*
@TODO fusionner les deux tableaux et supprimer les anciennes combinaisons reecrasee
*/
void Square::update(std::vector<Combi> combis)
{
	m_combis = combis;
}

Square::col Square::get_color() const
{
	return (m_col);
}

Square::pos Square::get_pos() const
{
	return (m_pos);
}

std::vector<Square::Combi> Square::get_combis() const
{
	return (m_combis);
}