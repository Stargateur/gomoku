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
	GVOText(std::string const &text);
	GVOText(std::string const &text, sf::Vector2f const &pos);
	~GVOText();
	virtual sf::Drawable*	getDrawable(void);
	virtual void			mouseClick(sf::Vector2f const &pos);
	virtual void			mouseMove(sf::Vector2f const &pos);
	virtual void			keyPressed(sf::Vector2f const &pos, sf::Uint32 const &key);

public:
	sf::Text	&getText(void);
	void		setPos(sf::Vector2f const &pos);

private:
	sf::Text					mText;
	sf::Font					mFont;
};

#endif // !GVOTEXT_HPP_
