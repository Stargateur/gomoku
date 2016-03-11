#include	"GVOInputBox.hpp"

GVOInputBox::GVOInputBox(std::string const &title, sf::Vector2f const &pos, sf::Vector2f const &size, std::string &content, std::mutex &mutex) :
	mTitle(title), mContent(content), mMutex(mutex), mTextPos(e_position::ALIGN_LEFT), mTextColor(sf::Color::Black)
{
	mFont.loadFromFile("Font/TCCEB.TTF");
	mText.setFont(mFont);
	mText.setColor(mTextColor);
	mText.setCharacterSize(24);
	mText.setPosition(sf::Vector2f(5, 0));

	mRendered.create(size.x, size.y);
	mBackground.setFillColor(sf::Color::White);
	mBackground.setSize(size);

	mSprite.setPosition(pos);
	updateRender();
}
GVOInputBox::~GVOInputBox(void)
{
	for(IGVAMouseHover* action : mHoverActions)
		delete action;
	for (IGVAMouseClick* action : mClickActions)
		delete action;
	for (IGVAKeyPressed* action : mKeyActions)
		delete action;
}

sf::Drawable	*GVOInputBox::getDrawable(void) { updateRender(); return &mSprite; }
sf::Text & GVOInputBox::getText(void) { return mText; }
void			GVOInputBox::addAction(IGVAMouseClick *action) { mClickActions.push_back(action); }
void			GVOInputBox::addAction(IGVAMouseHover *action) { mHoverActions.push_back(action); }
void			GVOInputBox::addAction(IGVAKeyPressed *action) { mKeyActions.push_back(action); }

void GVOInputBox::setTextPosition(e_position const &pos)
{
	mTextPos = pos;
}

void GVOInputBox::setTextColor(sf::Color const & color)
{
	mTextColor = color;
}

#include <iostream>
void				GVOInputBox::updateTextPosition(void)
{
	sf::Vector2f	pos;

	switch (mTextPos)
	{
	case e_position::ALIGN_LEFT:
		mText.setOrigin(sf::Vector2f(0, mText.getLocalBounds().height / 2 + mText.getLocalBounds().top / 2));
		pos.x = 5;
		pos.y = mBackground.getLocalBounds().height / 2 + mBackground.getLocalBounds().top / 2 - 3;
		break;
	case e_position::ALIGN_RIGHT:
		mText.setOrigin(sf::Vector2f(mText.getLocalBounds().width + mText.getLocalBounds().left, mText.getLocalBounds().height / 2 + mText.getLocalBounds().top / 2));
		pos.x = mBackground.getLocalBounds().width + mBackground.getLocalBounds().left - 5;
		pos.y = mBackground.getLocalBounds().height / 2 + mBackground.getLocalBounds().top / 2 - 3;
		break;
	case e_position::CENTERED:
		mText.setOrigin(sf::Vector2f(mText.getLocalBounds().width / 2 + mText.getLocalBounds().left, mText.getLocalBounds().height / 2 + mText.getLocalBounds().top / 2));
		pos.x = mBackground.getLocalBounds().width / 2 + mBackground.getLocalBounds().left / 2;
		pos.y = mBackground.getLocalBounds().height / 2 + mBackground.getLocalBounds().top / 2 - 3;
		break;
	default:
		break;
	}
	if (pos.y < 0)
		pos.y = 0;
	if (pos.x < 0)
		pos.x = 0;
	mText.setPosition(pos);
}

void			GVOInputBox::updateRender(void)
{
	mMutex.lock();
	if (mContent == "")
	{
		mText.setString(mTitle);
		mText.setColor(sf::Color(0, 0, 0, 125));
	}
	else
	{
		mText.setString(mContent);
		mText.setColor(mTextColor);
	}
	updateTextPosition();
	mMutex.unlock();
	mRendered.clear(sf::Color::Transparent);
	mRendered.draw(mBackground);
	mRendered.draw(mText);
	mRendered.display();
	mSprite.setTexture(mRendered.getTexture());
}

void			GVOInputBox::mouseClick(sf::Vector2f const &pos)
{
	if (mClickActions.empty() == false)
	{
		for (IGVAMouseClick* action : mClickActions)
			action->Act(mSprite, pos);
	}
}

void			GVOInputBox::mouseMove(sf::Vector2f const &pos)
{
	if (mHoverActions.empty() == false)
	{
		for (IGVAMouseHover* action : mHoverActions)
			action->Act(mSprite, pos);
	}
}

void			GVOInputBox::keyPressed(sf::Vector2f const &pos, sf::Uint32 const &key)
{
	for (IGVAKeyPressed* action : mKeyActions)
		action->Act(mSprite, pos, key);
}

void			GVOInputBox::setBackground(sf::Color const &color)
{
	mBackground.setFillColor(color);
}