#include	<cstdlib>
#include	"GomokuGraphics.hpp"
#include	"GVOButton.hpp"
#include	"GVOText.hpp"
#include	"GVOInputBox.hpp"
#include	"IGVObject.hpp"
#include	"PlayerInfo.hpp"
#include	"GameInfo.hpp"
#include	"GVAMouseClickCallBack.hpp"
#include	"GVAMouseClickTextureRect.hpp"
#include	"GVAMouseHoverChangeColor.hpp"
#include	"GVAKeyPressedFocusSave.hpp"
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
void		change_view(GomokuGraphics::e_view view)
{
	PlayerInfo::getInstance().lock();
	PlayerInfo::getInstance().mView = view;
	PlayerInfo::getInstance().unlock();
}
void		mute_speaker(int volume)
{
	PlayerInfo::getInstance().lock();
	PlayerInfo::getInstance().mMusicVolume = (PlayerInfo::getInstance().mMusicVolume - 75) * -1;
	PlayerInfo::getInstance().unlock();
}

void			GomokuGraphics::backgroundEffects(void)
{
	static int	effectState = 0;
	static int	effect = 1;
	if (effectState == 0)
	{
		effect = (effect - 1) * -1;
		effectState = 10000;
	}
	switch (effect)
	{
	// Zoom in
	case 0:
		mBackground.setScale(mBackground.getScale() + sf::Vector2f(0.000003, 0.000003));
		effectState--;
		break;
	// Zoom out
	case 1:
		mBackground.setScale(mBackground.getScale() - sf::Vector2f(0.000003, 0.000003));
		effectState--;
		break;
	}
}

sf::Vector2f	souris;
void			GomokuGraphics::init()
{
	// Création de la fenètre
	mWindow = new sf::RenderWindow(sf::VideoMode(WIN_X, WIN_Y, 32), "Hikaru no GO");

	//set loading screen
	GVOText *loading = new GVOText("Loading...");
	loading->setPos(sf::Vector2f(WIN_X / 2 - loading->getText().getGlobalBounds().width / 2, WIN_Y / 2 - loading->getText().getGlobalBounds().height / 2));
	mWindow->draw(*loading->getDrawable());
	mWindow->display();

	//charge texture
	TextureManager::getInstance().loadTexture("background", "Sprite/bg.jpg");
	TextureManager::getInstance().loadTexture("board", "Sprite/board.png");
	TextureManager::getInstance().loadTexture("connexion", "Sprite/connexion.png");
	TextureManager::getInstance().loadTexture("black", "Sprite/black.png");
	TextureManager::getInstance().loadTexture("white", "Sprite/white.png");
	TextureManager::getInstance().loadTexture("histo", "Sprite/histo.png");
	TextureManager::getInstance().loadTexture("home", "Sprite/home.png");
	TextureManager::getInstance().loadTexture("play", "Sprite/play.png");
	TextureManager::getInstance().loadTexture("speaker", "Sprite/speaker.png");
	TextureManager::getInstance().loadTexture("option", "Sprite/options.png");
	TextureManager::getInstance().getTexture("home").setSmooth(true);
	TextureManager::getInstance().getTexture("play").setSmooth(true);
	TextureManager::getInstance().getTexture("speaker").setSmooth(true);
	TextureManager::getInstance().getTexture("option").setSmooth(true);

	delete loading;

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
	mBackground.setTexture(TextureManager::getInstance().getTexture("background"));
	mBackground.setScale(sf::Vector2f(0.2, 0.2));
	mBackground.setColor(sf::Color(75, 75, 75, 125));
	mBackground.setOrigin(sf::Vector2f(mBackground.getLocalBounds().width / 2, mBackground.getLocalBounds().height / 2));
	mBackground.setPosition(sf::Vector2f(WIN_X / 2, WIN_Y / 2));

	//init game
	GVOButton *button2 = new GVOButton(sf::Vector2f(WIN_X / 4.8, 81.6), TextureManager::getInstance().getTexture("board"), sf::Vector2f(0.8, 0.8));
	button2->addAction(new GVAMouseClickCallBack<sf::Vector2f *>(click_plateau, (&souris)));
	mGameView.pushObject(button2);
	GVOButton *histo = new GVOButton(sf::Vector2f(0, 81.6), TextureManager::getInstance().getTexture("histo"), sf::Vector2f(0.8, 0.8));
	mGameView.pushObject(histo);

	//init menu
	GVOButton *btn = new GVOButton(sf::Vector2f(0, 0), TextureManager::getInstance().getTexture("home"), sf::Vector2f(0.5, 0.5));
	btn->addAction(new GVAMouseClickCallBack<GomokuGraphics::e_view>(change_view, GomokuGraphics::e_view::HOME));
	btn->addAction(new GVAMouseHoverChangeColor(sf::Color(sf::Uint8(210), sf::Uint8(255), sf::Uint8(210), sf::Uint8(180)), sf::Color(sf::Uint8(255), sf::Uint8(255), sf::Uint8(255), sf::Uint8(255))));
	mMenuView.pushObject(btn);
	btn = new GVOButton(sf::Vector2f(70, 0), TextureManager::getInstance().getTexture("play"), sf::Vector2f(0.5, 0.5));
	btn->addAction(new GVAMouseClickCallBack<GomokuGraphics::e_view>(change_view, GomokuGraphics::e_view::PLAY));
	btn->addAction(new GVAMouseHoverChangeColor(sf::Color(sf::Uint8(210), sf::Uint8(255), sf::Uint8(210), sf::Uint8(180)), sf::Color(sf::Uint8(255), sf::Uint8(255), sf::Uint8(255), sf::Uint8(255))));
	mMenuView.pushObject(btn);
	btn = new GVOButton(sf::Vector2f(140, 0), TextureManager::getInstance().getTexture("option"), sf::Vector2f(0.5, 0.5));
	btn->addAction(new GVAMouseClickCallBack<GomokuGraphics::e_view>(change_view, GomokuGraphics::e_view::CLIENT_OPTIONS));
	btn->addAction(new GVAMouseHoverChangeColor(sf::Color(sf::Uint8(210), sf::Uint8(255), sf::Uint8(210), sf::Uint8(180)), sf::Color(sf::Uint8(255), sf::Uint8(255), sf::Uint8(255), sf::Uint8(255))));
	mMenuView.pushObject(btn);
	btn = new GVOButton(sf::Vector2f(WIN_X - 34, WIN_Y - 34), TextureManager::getInstance().getTexture("speaker"), sf::Vector2f(0.25, 0.25));
	btn->addAction(new GVAMouseClickTextureRect(sf::IntRect(128, 0, 128, 128), sf::IntRect(0, 0, 128, 128)));
	btn->addAction(new GVAMouseClickCallBack<int>(mute_speaker, 0));
	btn->getSprite().setTextureRect(sf::IntRect(0, 0, 128, 128));
	btn->addAction(new GVAMouseHoverChangeColor(sf::Color(sf::Uint8(255), sf::Uint8(255), sf::Uint8(255), sf::Uint8(180)), sf::Color(sf::Uint8(255), sf::Uint8(255), sf::Uint8(255), sf::Uint8(255))));
	mMenuView.pushObject(btn);

	//init home
	GVOText *text = new GVOText("Ah, te revoila !", sf::Vector2f(WIN_X / 2 - 50, WIN_Y / 2 - 10));
	mHomeView.pushObject(text);

	//init options
	GVOText *t = new GVOText("PSEUDO :", sf::Vector2f(WIN_X / 2 - 150, WIN_Y / 2 - 100));
	mClientOptions.pushObject(t);
	GVOInputBox *ib = new GVOInputBox("", sf::Vector2f(WIN_X / 2 - 50, WIN_Y / 2 - 100), PlayerInfo::getInstance().mPseudo, PlayerInfo::getInstance().getMutex());
	ib->addAction(new GVAKeyPressedFocusSave(PlayerInfo::getInstance().mPseudo, PlayerInfo::getInstance().getMutex()));
	ib->addAction(new GVAMouseHoverChangeColor(sf::Color(150, 150, 255, 255), sf::Color(255, 255, 255, 255)));
	mClientOptions.pushObject(ib);

	//init theme sound
	if (!mThemeSound.openFromFile("Sound/theme.ogg"))
	{
		std::cout << "error loading sound" << std::endl;
	}
	else { mThemeSound.play(); mThemeSound.setLoop(true); }

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
	sf::String test;
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
				souris = mWindow->mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
				mMenuView.mouseMove(mWindow->mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y)));
				mCurrentView->mouseMove(mWindow->mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y)));
			}
			else if (event.type == sf::Event::KeyPressed)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) == true)
					mWindow->close();
			}
			if (event.type == sf::Event::TextEntered)
			{

				mMenuView.keyPressed(mWindow->mapPixelToCoords(sf::Mouse::getPosition(*mWindow)), event.text.unicode);
				mCurrentView->keyPressed(mWindow->mapPixelToCoords(sf::Mouse::getPosition(*mWindow)), event.text.unicode);
			}
		}
		// check actual state
		checkClientUpdates();
		updateView();
		backgroundEffects();
		//clear
		mWindow->clear();
		//draw all Sprites
		std::list<sf::Drawable *> mylist = mCurrentView->getDrawables();
		std::list<sf::Drawable *> myMenu = mMenuView.getDrawables();
		mWindow->draw(mBackground);
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

void GomokuGraphics::updateView(void)
{
	PlayerInfo::getInstance().lock();
	//std::cout << "valeur de view: " << PlayerInfo::getInstance().mView << std::endl;
	switch (PlayerInfo::getInstance().mView)
	{
	case GomokuGraphics::e_view::HOME:
		mCurrentView = &mHomeView;
		break;
	case GomokuGraphics::e_view::PLAY:
		if (PlayerInfo::getInstance().mConnect == PlayerInfo::STATE::DONE)
			mCurrentView = &mGameView;
		else
			mCurrentView = &mConnectView;
		break;
	case GomokuGraphics::e_view::CLIENT_OPTIONS:
		mCurrentView = &mClientOptions;
	default:
		break;
	}
	PlayerInfo::getInstance().unlock();
}

void GomokuGraphics::checkClientUpdates(void)
{
	PlayerInfo::getInstance().lock();
	//check sound
	if (PlayerInfo::getInstance().mMusicVolume != mThemeSound.getVolume())
		mThemeSound.setVolume(PlayerInfo::getInstance().mMusicVolume);
	// check connection
	if (PlayerInfo::getInstance().mDisconnect == PlayerInfo::STATE::DONE)
	{
		PlayerInfo::getInstance().mDisconnect = PlayerInfo::STATE::NOTHING;
		PlayerInfo::getInstance().mConnect = PlayerInfo::STATE::NOTHING;
		GameInfo::getInstance().lock();
		GameInfo::getInstance().reset();
		GameInfo::getInstance().unlock();
		reset();
	}
	else if (PlayerInfo::getInstance().mConnect == PlayerInfo::STATE::DONE)
	{
		PlayerInfo::getInstance().mDisconnect = PlayerInfo::STATE::NOTHING;
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
	}
	PlayerInfo::getInstance().unlock();
}