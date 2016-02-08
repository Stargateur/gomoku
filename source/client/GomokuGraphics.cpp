#include	"GomokuGraphics.hpp"
#include	"GVOButton.hpp"
#include	"IGVObject.hpp"

GomokuGraphics::GomokuGraphics()
{
	mCurrentView = &mGameView;
}

GomokuGraphics::~GomokuGraphics()
{
}

void GomokuGraphics::init()
{
	mWindow = new sf::RenderWindow(sf::VideoMode(WIN_X, WIN_Y, 32), "Hikaru no GO");
	//charge texture
	if (!mTextureBackground.loadFromFile("C:/Users/degand_a/Projects/gomoku/Sprite/board.png", sf::IntRect(0, 0, 798, 798)))
	{std::cerr << "Cant load the texture" << std::endl;}
	if (!mTopTexture.loadFromFile("C:/Users/degand_a/Projects/gomoku/Sprite/connexion.png", sf::IntRect(0, 0, 1920, 1080)))
	{std::cerr << "Cant load the texture" << std::endl;}
	//set sprites
	//Background
	mGameView.mObjects.push_back(new GVOButton(sf::Vector2f(WIN_X / 3, 0), mTextureBackground, sf::Vector2f(0.8, 0.8)));
}

void GomokuGraphics::run()
{
	while (mWindow->isOpen())
	{
		sf::Event event;
		while (mWindow->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				mWindow->close();
			if (event.type == sf::Event::MouseButtonReleased)
			{
				std::cout << "clik" << std::endl;
			}
		}
		//clear
		mWindow->clear();
		//draw all Sprites
		std::list<sf::Sprite *> mylist = mCurrentView->getSprites();
		for (sf::Sprite *aff : mylist)
		{
			mWindow->draw(*aff);
		}
		//aff display
		mWindow->display();
	}
}
