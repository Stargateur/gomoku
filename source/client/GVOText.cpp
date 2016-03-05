#include	<SFML/Graphics.hpp>
#include	"GVOText.hpp"

GVOText::GVOText(std::string const &text, sf::Vector2f const &pos) : mPos(pos)
{
	mFont.loadFromFile("Font/TCCEB.TTF");
	mText.setFont(mFont);
	mText.setString(text);
	mText.setPosition(pos);
	mText.setColor(sf::Color::White);
	mText.setCharacterSize(24);
}

GVOText::~GVOText()
{
	for (IGVAMouseHover* action : mHoverActions)
		delete action;
	for (IGVAMouseClick* action : mClickActions)
		delete action;
}

sf::Drawable	*GVOText::getDrawable(void) { return &mText; }
void			GVOText::mouseClick(sf::Vector2f const & pos) {}
void			GVOText::mouseMove(sf::Vector2f const & pos) {}
