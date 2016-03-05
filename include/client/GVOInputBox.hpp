#pragma once

#ifndef GVOINPUTBOX_HPP_
#define GVOINPUTBOX_HPP_

#include	<SFML/Graphics.hpp>
#include	"IGVObject.hpp"

class GVOInputBox : public IGVObject
{
public:
	GVOInputBox(std::string const &title, sf::Vector2f const &pos);
	virtual ~GVOInputBox(void);
	virtual sf::Drawable	*getDrawable(void);
	virtual void			mouseClick(sf::Vector2f const &pos);
	virtual void			mouseMove(sf::Vector2f const &pos);

private:
	void	updateRender(void);

private:
	sf::Sprite			mSprite;
	sf::RenderTexture	mRendered;
	sf::Text			mText;
	sf::Font			mFont;
	std::string			mTitle;
	std::string			mInputSave;
};


#endif // !GVOINPUTBOX_HPP_
