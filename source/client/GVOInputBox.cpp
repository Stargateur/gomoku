#include	"GVOInputBox.hpp"

GVOInputBox::GVOInputBox(std::string const &title, sf::Vector2f const &pos, std::string &content, std::mutex &mutex) : mTitle(title), mContent(content), mMutex(mutex)
{
	mFont.loadFromFile("Font/TCCEB.TTF");
	mText.setFont(mFont);
	mText.setPosition(sf::Vector2f(5,0));
	mText.setColor(sf::Color::Black);
	mText.setCharacterSize(24);

	mRendered.create(200, 30);
	mBackground.setFillColor(sf::Color::White);
	mBackground.setSize(sf::Vector2f(200, 30));

	mSprite.setPosition(pos);
	updateRender();
}
GVOInputBox::~GVOInputBox(void) {}

sf::Drawable	*GVOInputBox::getDrawable(void) { updateRender(); return &mSprite; }
void			GVOInputBox::addAction(IGVAMouseClick *action) { mClickActions.push_back(action); }
void			GVOInputBox::addAction(IGVAMouseHover *action) { mHoverActions.push_back(action); }
void			GVOInputBox::addAction(IGVAKeyPressed *action) { mKeyActions.push_back(action); }
void			GVOInputBox::updateRender(void)
{
	mMutex.lock();
	mText.setString(mTitle + mContent);
	mMutex.unlock();
	mRendered.clear();
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
