#include	<SFML/Graphics.hpp>
#include	"GVOText.hpp"

GVOText::GVOText(std::string const &text)
{
	mFont.loadFromFile("Font/TCCEB.TTF");
	mText.setFont(mFont);
	mText.setString(text);
	mText.setColor(sf::Color::White);
	mText.setCharacterSize(24);
}

GVOText::GVOText(std::string const &text, sf::Vector2f const &pos)
{
	mFont.loadFromFile("Font/TCCEB.TTF");
	mText.setFont(mFont);
	mText.setString(text);
	mText.setPosition(pos);
	mText.setColor(sf::Color::White);
	mText.setCharacterSize(24);
}

GVOText::~GVOText() {}

sf::Drawable	*GVOText::getDrawable(void) { return &mText; }
sf::Text		&GVOText::getText(void) { return mText; }
void GVOText::setPos(sf::Vector2f const &pos)
{
	mText.setPosition(pos);
}
void			GVOText::framePassed(void) {}
void			GVOText::mouseClick(sf::Vector2f const &pos) {}
void			GVOText::mouseMove(sf::Vector2f const &pos) {}
void			GVOText::keyPressed(sf::Vector2f const &pos, sf::Uint32 const &key) {}
