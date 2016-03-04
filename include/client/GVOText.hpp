#pragma once

#ifndef GVOTEXT_HPP_
#define GVOTEXT_HPP_

#include	<SFML/Graphics.hpp>
#include	<list>
#include	"IGVObject.hpp"
#include	"IGVAMouseClick.hpp"
#include	"IGVAMouseHover.hpp"

class GVOText : public IGVObject
{
public:
	GVOText(std::string const &text, sf::Vector2f const &pos);
	~GVOText();
	virtual sf::Drawable*	getDrawable(void);
	virtual void			mouseClick(sf::Vector2f const & pos);
	virtual void			mouseMove(sf::Vector2f const &pos);

private:
	sf::Text					mText;
	sf::Font					mFont;
	sf::Vector2f				mPos;
	std::list<IGVAMouseClick *>	mClickActions;
	std::list<IGVAMouseHover *>	mHoverActions;
};

#endif // !GVOTEXT_HPP_
