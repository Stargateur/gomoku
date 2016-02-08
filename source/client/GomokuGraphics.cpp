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

void		click_plateau(sf::Vector2f *param)
{
	std::cout << "click sur le plateau" << std::endl;
	if (param != NULL)
	{
		std::cout << "x:" << param->x << " y:" << param->y << std::endl;
	}
}
sf::Vector2f souris;
void GomokuGraphics::init()
{
	mWindow = new sf::RenderWindow(sf::VideoMode(WIN_X, WIN_Y, 32), "Hikaru no GO");
	//charge texture
	if (!mTextureBackground.loadFromFile("C:/Users/Elliott/Epitech/gomoku/Sprite/board.png", sf::IntRect(0, 0, 798, 798)))
	{std::cerr << "Cant load the texture" << std::endl;}
	if (!mTopTexture.loadFromFile("C:/Users/Elliott/Epitech/gomoku/Sprite/connexion.png", sf::IntRect(0, 0, 1920, 1080)))
	{std::cerr << "Cant load the texture" << std::endl;}
	//set sprites
	//Background
	GVOButton<sf::Vector2f *> *button = new GVOButton<sf::Vector2f *>(sf::Vector2f(WIN_X / 4.8, 81.6), mTextureBackground, sf::Vector2f(0.8, 0.8));
	button->setAction(&click_plateau, &souris);
	mGameView.pushObject(button);
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
				souris.x = event.mouseButton.x;
				souris.y = event.mouseButton.y;
				mCurrentView->mouseClick(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
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
