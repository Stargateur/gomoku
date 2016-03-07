#pragma once

#ifndef GVOINPUTBOX_HPP_
#define GVOINPUTBOX_HPP_

#include	<SFML/Graphics.hpp>
#include	<mutex>
#include	<list>
#include	"IGVObject.hpp"
#include	"IGVAMouseClick.hpp"
#include	"IGVAMouseHover.hpp"
#include	"IGVAKeyPressed.hpp"

class GVOInputBox : public IGVObject
{
public:
	enum e_position
	{
		CENTERED,
		ALIGN_LEFT,
		ALIGN_RIGHT
	};

public:
	GVOInputBox(std::string const &title, sf::Vector2f const &pos, sf::Vector2f const &size, std::string &content, std::mutex &mutex);
	virtual ~GVOInputBox(void);
	virtual sf::Drawable	*getDrawable(void);
	virtual void			mouseClick(sf::Vector2f const &pos);
	virtual void			mouseMove(sf::Vector2f const &pos);
	virtual void			keyPressed(sf::Vector2f const &pos, sf::Uint32 const &key);

public:
	void	addAction(IGVAMouseClick *action);
	void	addAction(IGVAMouseHover *action);
	void	addAction(IGVAKeyPressed *action);
	void	setTextPosition(e_position const &pos);

private:
	void	updateRender(void);
	void	updateTextPosition(void);

private:
	sf::Sprite			mSprite;
	sf::RenderTexture	mRendered;
	sf::RectangleShape	mBackground;
	sf::Text			mText;
	sf::Font			mFont;
	std::string			mTitle;
	std::string			&mContent;
	std::mutex			&mMutex;
	e_position			mTextPos;

private:
	std::list<IGVAMouseClick *>	mClickActions;
	std::list<IGVAMouseHover *>	mHoverActions;
	std::list<IGVAKeyPressed *> mKeyActions;
};


#endif // !GVOINPUTBOX_HPP_
