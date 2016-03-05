#pragma once

#ifndef GVOBUTTON_HPP__
#define GVOBUTTON_HPP__

#include	<SFML/Graphics.hpp>
#include	<list>
#include	"IGVObject.hpp"
#include	"IGVAMouseClick.hpp"
#include	"IGVAMouseHover.hpp"
#include	"IGVAKeyPressed.hpp"

class GVOButton : public IGVObject
{
public:
	GVOButton(sf::Vector2f pos, sf::Texture const &texture, sf::Vector2f const &scale);
	virtual ~GVOButton();
	virtual sf::Drawable*	getDrawable(void);
	sf::Sprite				&getSprite(void);

public:
	void	addAction(IGVAMouseClick *action);
	void	addAction(IGVAMouseHover *action);
	void	addAction(IGVAKeyPressed *action);
	void	mouseClick(sf::Vector2f const &pos);
	void	mouseMove(sf::Vector2f const &pos);
	void	keyPressed(sf::Vector2f const &pos, sf::Uint32 const &key);

private:
	sf::Sprite					mSprite;
	sf::Vector2f				mPos;
	std::list<IGVAMouseClick *>	mClickActions;
	std::list<IGVAMouseHover *>	mHoverActions;
	std::list<IGVAKeyPressed *>	mKeyActions;
};

#endif // !GVOBUTTON_HPP__
