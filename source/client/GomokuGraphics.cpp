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
		std::cout << "Asking connection" << std::endl;
		PlayerInfo::getInstance().mHost = params;
		PlayerInfo::getInstance().mConnect = PlayerInfo::STATE::ASK;
		PlayerInfo::getInstance().unlock();
	}
}

GomokuGraphics::GomokuGraphics()
{
	for (size_t i = 0; i < 19; i++)
	{
		for (size_t j = 0; j < 19; j++)
		{
			mStones[i][j] = nullptr;
		}
	}
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
				float tryX = xStart + x * 33.5;
				float tryY = yStart + y * 33.5;
				if ((param->x <= tryX + 10 && param->x >= tryX - 10) &&
					(param->y <= tryY + 10 && param->y >= tryY - 10))
				{
					std::cout << "LA BISCOTTE : " << x << " | " << y << std::endl;
					PlayerInfo::getInstance().lock();
					PlayerInfo::getInstance().mLastPlay.x = x;
					PlayerInfo::getInstance().mLastPlay.y = y;
					if (PlayerInfo::getInstance().mColor.compare("black") == 0)
						PlayerInfo::getInstance().mLastPlay.color = PlayerInfo::getInstance().mLastPlay.Black;
					else
						PlayerInfo::getInstance().mLastPlay.color = PlayerInfo::getInstance().mLastPlay.White;
					PlayerInfo::getInstance().mWantPlay = PlayerInfo::STATE::ASK;
					PlayerInfo::getInstance().unlock();
				}
			}
		}
		std::cout << "x:" << param->x << " y:" << param->y << std::endl;
	}
}
void		change_color(std::string color)
{
	PlayerInfo::getInstance().lock();
	PlayerInfo::getInstance().mColor = color;
	std::cout << "You are now " << color << std::endl;
	PlayerInfo::getInstance().unlock();
}
sf::Vector2f souris;
void GomokuGraphics::init()
{
	mWindow = new sf::RenderWindow(sf::VideoMode(WIN_X, WIN_Y, 32), "Hikaru no GO");
	//charge texture
	if (!mTextureBackground.loadFromFile("Sprite/board.png", sf::IntRect(0, 0, 798, 798)))
	{std::cerr << "Cant load the texture" << std::endl;}
	if (!mTopTexture.loadFromFile("Sprite/connexion.png", sf::IntRect(0, 0, 1920, 1080)))
	{std::cerr << "Cant load the texture" << std::endl;}
	if (!mBlackTexture.loadFromFile("Sprite/black.png", sf::IntRect(0, 0, 1920, 1080)))
	{std::cerr << "Cant load the texture" << std::endl;}
	if (!mWhiteTexture.loadFromFile("Sprite/white.png", sf::IntRect(0, 0, 1920, 1080)))
	{std::cerr << "Cant load the texture" << std::endl;}
	//set sprites
	mCurrentView = &mConnectView;
	GVOButton<std::string> *button = new GVOButton<std::string>(sf::Vector2f(WIN_X / 2 - mTopTexture.getSize().x / 2, 2 * WIN_Y / 3), mTopTexture, sf::Vector2f(0.8, 0.8));
	button->setAction(connect, "localhost");
	mConnectView.pushObject(button);
	button = new GVOButton<std::string>(sf::Vector2f(WIN_X / 3 - mBlackTexture.getSize().x / 2, WIN_Y / 3), mBlackTexture, sf::Vector2f(0.8, 0.8));
	button->setAction(change_color, "black");
	mConnectView.pushObject(button);
	button = new GVOButton<std::string>(sf::Vector2f(2 * WIN_X / 3 - mWhiteTexture.getSize().x / 2, WIN_Y / 3), mWhiteTexture, sf::Vector2f(0.8, 0.8));
	button->setAction(change_color, "white");
	mConnectView.pushObject(button);
	//Background
	GVOButton<sf::Vector2f *> *button2 = new GVOButton<sf::Vector2f *>(sf::Vector2f(WIN_X / 4.8, 81.6), mTextureBackground, sf::Vector2f(0.8, 0.8));
	button2->setAction(&click_plateau, &souris);
	mGameView.pushObject(button2);
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
			affStone();
		}
		//aff display
		mWindow->display();
	}
}

void GomokuGraphics::affStone()
{
	GameInfo::getInstance().lock(); 
	for (size_t x = 0; x < 19; x++)
	{
		for (size_t y = 0; y < 19; y++)
		{
			if (GameInfo::getInstance().mPlate[x][y] == ITCP_protocol<ITCP_client>::Game_stone::Color::Black ||
				GameInfo::getInstance().mPlate[x][y] == ITCP_protocol<ITCP_client>::Game_stone::Color::White)
			{
				if (mStones[x][y] == nullptr)
				{
					GVOButton<int> *button = nullptr;
					if (GameInfo::getInstance().mPlate[x][y] == ITCP_protocol<ITCP_client>::Game_stone::Color::Black)
						button = new GVOButton<int>(sf::Vector2f(225 + x * 33.5, 80 + y * 33.5), mBlackTexture, sf::Vector2f(0.8, 0.8));
					if (GameInfo::getInstance().mPlate[x][y] == ITCP_protocol<ITCP_client>::Game_stone::Color::White)
						button = new GVOButton<int>(sf::Vector2f(225 + x * 33.5, 80 + y * 33.5), mWhiteTexture, sf::Vector2f(0.8, 0.8));
					mStones[x][y] = button;
					mGameView.pushObject(button);
				}
			}
			else
			{
				if (mStones[x][y] != nullptr)
				{
					mGameView.removeObject(mStones[x][y]);
					mStones[x][y] = nullptr;
				}
			}
		}
	}
	GameInfo::getInstance().unlock();
}

void GomokuGraphics::checkClientUpdates(void)
{
	PlayerInfo::getInstance().lock();
	// check connection
	if (PlayerInfo::getInstance().mDisconnect == PlayerInfo::STATE::DONE)
	{
		PlayerInfo::getInstance().mDisconnect = PlayerInfo::STATE::NOTHING;
		PlayerInfo::getInstance().mConnect = PlayerInfo::STATE::NOTHING;
		mCurrentView = &mConnectView;
	}
	else if (PlayerInfo::getInstance().mConnect == PlayerInfo::STATE::DONE)
	{
		PlayerInfo::getInstance().mDisconnect = PlayerInfo::STATE::NOTHING;
		mCurrentView = &mGameView;
	}
	else if (PlayerInfo::getInstance().mConnect == PlayerInfo::STATE::FAILED)
	{
		PlayerInfo::getInstance().mConnect = PlayerInfo::STATE::NOTHING;
		PlayerInfo::getInstance().mDisconnect = PlayerInfo::STATE::NOTHING;
		std::cout << PlayerInfo::getInstance().mErrorMessage << std::endl;
		mCurrentView = &mConnectView;
	}
	PlayerInfo::getInstance().unlock();
}