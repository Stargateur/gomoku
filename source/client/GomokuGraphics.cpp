#include	"GomokuGraphics.hpp"
#include	"GVOButton.hpp"
#include	"IGVObject.hpp"
#include	"PlayerInfo.hpp"
#include	"GameInfo.hpp"

void		connect(std::string params)
{
	if (params.empty() == false)
	{
		PlayerInfo::getInstance().lock();
		PlayerInfo::getInstance().mHost = params;
		PlayerInfo::getInstance().mWantConnect = true;
		PlayerInfo::getInstance().unlock();
	}
}

GomokuGraphics::GomokuGraphics()
{
	mCurrentView = &mConnectView;
	if (!mTopTexture.loadFromFile("../Sprite/connexion.png", sf::IntRect(0, 0, 1920, 1080)))
		std::cerr << "Cant load the texture" << std::endl;
	GVOButton<std::string> *button = new GVOButton<std::string>(sf::Vector2f(WIN_X / 4.8, 81.6), mTopTexture, sf::Vector2f(0.8, 0.8));
	button->setAction(connect, "localhost");
	mConnectView.pushObject(button);
}

GomokuGraphics::~GomokuGraphics()
{
}

void		click_plateau(sf::Vector2f *param)
{
	std::cout << "click sur le plateau" << std::endl;
	size_t		xStart = 242;
	size_t		yStart = 98;
	size_t		prec = 10;
	if (param != NULL)
	{
		for (size_t x = 0; x < 19; x++)
		{
			for (size_t y = 0; y < 19; y++)
			{
				size_t tryX = xStart + x * 33;
				size_t tryY = yStart + y * 33;
				if ((param->x <= tryX + 10 && param->x >= tryX - 10) &&
					(param->y <= tryY + 10 && param->y >= tryY - 10))
				{
					std::cout << "LA BISCOTTE : " << x << " | " << y << std::endl;
					PlayerInfo::getInstance().lock();
					PlayerInfo::getInstance().mLastPlay.x = x;
					PlayerInfo::getInstance().mLastPlay.y = y;
					PlayerInfo::getInstance().mLastPlay.color = PlayerInfo::getInstance().mLastPlay.Black;
					PlayerInfo::getInstance().mWantPlay = true;
					PlayerInfo::getInstance().unlock();
				}
			}
		}
		std::cout << "x:" << param->x << " y:" << param->y << std::endl;
	}
}
sf::Vector2f souris;
void GomokuGraphics::init()
{
	mWindow = new sf::RenderWindow(sf::VideoMode(WIN_X, WIN_Y, 32), "Hikaru no GO");
	//charge texture
	if (!mTextureBackground.loadFromFile("../Sprite/board.png", sf::IntRect(0, 0, 798, 798)))
	{std::cerr << "Cant load the texture" << std::endl;}
	if (!mTopTexture.loadFromFile("../Sprite/connexion.png", sf::IntRect(0, 0, 1920, 1080)))
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
				souris = mWindow->mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
				mCurrentView->mouseClick(mWindow->mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y)));
				std::cout << "clik" << std::endl;
			}
		}
		// check actual state
		checkClientUpdates();
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

void GomokuGraphics::checkClientUpdates(void)
{
	PlayerInfo::getInstance().lock();
	// check connection
	if (PlayerInfo::getInstance().mWantConnect == true)
	{
		if (PlayerInfo::getInstance().mHasFailed)
		{
			std::cout << PlayerInfo::getInstance().mErrorMessage << std::endl;
			PlayerInfo::getInstance().mHasFailed = false;
			PlayerInfo::getInstance().mWantConnect = false;
		}
		else if (PlayerInfo::getInstance().mIsConnected)
		{
			PlayerInfo::getInstance().mWantConnect = false;
			mCurrentView = &mGameView;
		}
	}
	else if (PlayerInfo::getInstance().mHasFailed && !PlayerInfo::getInstance().mIsConnected)
	{
		std::cout << PlayerInfo::getInstance().mErrorMessage << std::endl;
		PlayerInfo::getInstance().mHasFailed = false;
		mCurrentView = &mConnectView;
	}
	PlayerInfo::getInstance().unlock();
}