#include	"GVOInputBox.hpp"

GVOInputBox::GVOInputBox(std::string const &title, sf::Vector2f const &pos) : mTitle(title)
{
	mFont.loadFromFile("Font/TCCEB.TTF");
	mText.setFont(mFont);
	mText.setPosition(sf::Vector2f(5,0));
	mText.setColor(sf::Color(100,100,100,180));
	mText.setCharacterSize(24);

	mRendered.create(200, 30);
	sf::RectangleShape background;
	background.setFillColor(sf::Color::White);
	background.setSize(sf::Vector2f(200, 30));
	mRendered.draw(background);

	mSprite.setPosition(pos);
	updateRender();
}
GVOInputBox::~GVOInputBox(void) {}
sf::Drawable	*GVOInputBox::getDrawable(void) { return &mSprite; }
void			GVOInputBox::updateRender(void)
{
	mText.setString(mTitle + mInputSave);
	mRendered.draw(mText);
	mRendered.display();
	mSprite.setTexture(mRendered.getTexture());
}

void			GVOInputBox::mouseClick(sf::Vector2f const &pos) {}
void			GVOInputBox::mouseMove(sf::Vector2f const &pos) {}
