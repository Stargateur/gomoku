#include	"GomokuGraphics.hpp"
#include	"GVOButton.hpp"
#include	"IGVObject.hpp"
#include	"PlayerInfo.hpp"
#include	"GameInfo.hpp"
#include	"GVAMouseClickCallBack.hpp"
#include	"GVAMouseHoverChangeColor.hpp"
#include	"TextureManager.hpp"

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
		for (size_t j = 0; j < 19; j++)
			mStones[i][j] = nullptr;
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
	TextureManager::getInstance().loadTexture("board", "Sprite/board.png");
	TextureManager::getInstance().loadTexture("connexion", "Sprite/connexion.png");
	TextureManager::getInstance().loadTexture("black", "Sprite/black.png");
	TextureManager::getInstance().loadTexture("white", "Sprite/white.png");
	TextureManager::getInstance().loadTexture("histo", "Sprite/histo.png");
	TextureManager::getInstance().loadTexture("home", "Sprite/home.png");
	TextureManager::getInstance().getTexture("home").setSmooth(true);

	//set sprites
	GVOButton *button = new GVOButton(sf::Vector2f(WIN_X / 2 - TextureManager::getInstance().getTexture("connexion").getSize().x / 2, 2 * WIN_Y / 3), TextureManager::getInstance().getTexture("connexion"), sf::Vector2f(0.8, 0.8));
	button->addAction(new GVAMouseClickCallBack<std::string>(connect, std::string("localhost")));
	mConnectView.pushObject(button);
	button = new GVOButton(sf::Vector2f(WIN_X / 3 - TextureManager::getInstance().getTexture("black").getSize().x / 2, WIN_Y / 3), TextureManager::getInstance().getTexture("black"), sf::Vector2f(0.8, 0.8));
	button->addAction(new GVAMouseClickCallBack<std::string>(change_color, std::string("black")));
	mConnectView.pushObject(button);
	button = new GVOButton(sf::Vector2f(2 * WIN_X / 3 - TextureManager::getInstance().getTexture("white").getSize().x / 2, WIN_Y / 3), TextureManager::getInstance().getTexture("white"), sf::Vector2f(0.8, 0.8));
	button->addAction(new GVAMouseClickCallBack<std::string>(change_color, std::string("white")));
	mConnectView.pushObject(button);
	//Background
	GVOButton *button2 = new GVOButton(sf::Vector2f(WIN_X / 4.8, 81.6), TextureManager::getInstance().getTexture("board"), sf::Vector2f(0.8, 0.8));
	button2->addAction(new GVAMouseClickCallBack<sf::Vector2f *>(click_plateau, (&souris)));
	mGameView.pushObject(button2);
	GVOButton *histo = new GVOButton(sf::Vector2f(0, 81.6), TextureManager::getInstance().getTexture("histo"), sf::Vector2f(0.8, 0.8));
	mGameView.pushObject(histo);

	//init menu
	GVOButton *btn = new GVOButton(sf::Vector2f(0, 0), TextureManager::getInstance().getTexture("home"), sf::Vector2f(0.5, 0.5));
	btn->addAction(new GVAMouseHoverChangeColor(sf::Color(sf::Uint8(210), sf::Uint8(255), sf::Uint8(210), sf::Uint8(180)), sf::Color(sf::Uint8(255), sf::Uint8(255), sf::Uint8(255), sf::Uint8(255))));
	mMenuView.pushObject(btn);
	//btn = new GVOButton<void>(sf::Vector2f(200, 0), mTopTexture, sf::Vector2f(0.8, 0.8));
	//mMenuView.pushObject(btn);
	//btn = new GVOButton<void>(sf::Vector2f(400, 0), mTopTexture, sf::Vector2f(0.8, 0.8));
	//mMenuView.pushObject(btn);
	//btn = new GVOButton<void>(sf::Vector2f(600, 0), mTopTexture, sf::Vector2f(0.8, 0.8));
	//mMenuView.pushObject(btn);

	//init home


	//set home view
	mCurrentView = &mHomeView;
}

void GomokuGraphics::reset(void)
{
	for (size_t i = 0; i < 19; i++)
	{
		for (size_t j = 0; j < 19; j++)
		{
			if (mStones[i][j] != nullptr)
				mGameView.removeObject(mStones[i][j]);
			mStones[i][j] = nullptr;
		}
	}
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
			else if (event.type == sf::Event::MouseButtonReleased)
			{
				souris = mWindow->mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
				mMenuView.mouseClick(mWindow->mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y)));
				mCurrentView->mouseClick(mWindow->mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y)));
			}
			else if (event.type == sf::Event::MouseMoved)
			{
				std::cout << "moved" << std::endl;
				mMenuView.mouseMove(mWindow->mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y)));
				mCurrentView->mouseMove(mWindow->mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y)));
			}
			else if (event.type == sf::Event::KeyPressed)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) == true)
					mWindow->close();
			}
		}
		// check actual state
		checkClientUpdates();
		//clear
		mWindow->clear();
		//draw all Sprites
		std::list<sf::Drawable *> mylist = mCurrentView->getDrawables();
		std::list<sf::Drawable *> myMenu = mMenuView.getDrawables();
		for (sf::Drawable *aff : mylist)
		{
			if (aff != nullptr)
				mWindow->draw(*aff);
		}
		affStone();
		for (sf::Drawable *aff : myMenu)
		{
			if (aff != nullptr)
				mWindow->draw(*aff);
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
			if (GameInfo::getInstance().mPlate[x][y] == iprotocol::Game_stone::Color::Black ||
				GameInfo::getInstance().mPlate[x][y] == iprotocol::Game_stone::Color::White)
			{
				if (mStones[x][y] == nullptr)
				{
					GVOButton *button = nullptr;
					if (GameInfo::getInstance().mPlate[x][y] == iprotocol::Game_stone::Color::Black)
						button = new GVOButton(sf::Vector2f(225 + x * 33.5, 80 + y * 33.5), TextureManager::getInstance().getTexture("black"), sf::Vector2f(0.8, 0.8));
					if (GameInfo::getInstance().mPlate[x][y] == iprotocol::Game_stone::Color::White)
						button = new GVOButton(sf::Vector2f(225 + x * 33.5, 80 + y * 33.5), TextureManager::getInstance().getTexture("white"), sf::Vector2f(0.8, 0.8));
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
		GameInfo::getInstance().lock();
		GameInfo::getInstance().reset();
		GameInfo::getInstance().unlock();
		reset();
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
		GameInfo::getInstance().lock();
		GameInfo::getInstance().reset();
		GameInfo::getInstance().unlock();
		reset();
		mCurrentView = &mConnectView;
	}
	PlayerInfo::getInstance().unlock();
}