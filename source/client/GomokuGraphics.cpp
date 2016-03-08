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

void		connect(int u)
{
	PlayerInfo::getInstance().lock();
	std::cout << "Asking connection" << std::endl;
	PlayerInfo::getInstance().mConnect = PlayerInfo::STATE::ASK;
	PlayerInfo::getInstance().unlock();
}

void		connect_room(std::string room)
{
	GameInfo::getInstance().lock();
	if (GameInfo::getInstance().mConnected == PlayerInfo::STATE::NOTHING || GameInfo::getInstance().mConnected == PlayerInfo::STATE::FAILED)
	{
		std::cout << "connecting to " << room << "..." << std::endl;
		GameInfo::getInstance().mName = room;
		GameInfo::getInstance().mConnected = PlayerInfo::STATE::ASK;
	}
	GameInfo::getInstance().unlock();
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
	PlayerInfo::getInstance().mMusicMute = !PlayerInfo::getInstance().mMusicMute;
	PlayerInfo::getInstance().unlock();
}
void		change_volume(float volume)
{
	PlayerInfo::getInstance().lock();
	PlayerInfo::getInstance().mMusicVolume += volume;
	if (PlayerInfo::getInstance().mMusicVolume < 0)
		PlayerInfo::getInstance().mMusicVolume = 0;
	else if (PlayerInfo::getInstance().mMusicVolume > 100)
		PlayerInfo::getInstance().mMusicVolume = 100;
	PlayerInfo::getInstance().mStringVolume = std::to_string(static_cast<int>(PlayerInfo::getInstance().mMusicVolume));
	PlayerInfo::getInstance().unlock();
}

void		refresh_games(PlayerInfo::STATE state)
{
	GameInfo::getInstance().lock();
	GameInfo::getInstance().mUpdateRooms = state;
	GameInfo::getInstance().unlock();
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

void GomokuGraphics::showGames(int page)
{
	GVOButton		*game;
	GameInfo::getInstance().lock();
	if (GameInfo::getInstance().mUpdateRooms == PlayerInfo::STATE::ASK)
	{
		GameInfo::getInstance().mUpdateRooms = PlayerInfo::STATE::DOING;
		while ((page - 1) * PAGE_GAME_COUNT > GameInfo::getInstance().mRoomlist.size())
			page--;
		if (page < 1)
			page = 1;
		std::cout << "doing page " << page << std::endl;
		for (GVOButton *btn : GameInfo::getInstance().mGamelist)
		{
			if (btn->mText != nullptr)
				mGameListView.removeObject(btn->mText);
			mGameListView.removeObject(btn);
			delete btn;
		}
		GameInfo::getInstance().mGamelist.clear();
		int j = 0;
		for (int i = (page - 1) * PAGE_GAME_COUNT; i < page * PAGE_GAME_COUNT; i++)
		{
			if (i >= GameInfo::getInstance().mRoomlist.size())
				break;
			game = new GVOButton(sf::Vector2f(WIN_X / 2 - 150, WIN_Y / 2 + (50 * j)), TextureManager::getInstance().getTexture("connexion"), sf::Vector2f(1, 1));
			game->mText = new GVOText(*GameInfo::getInstance().mRoomlist.at(j)->name, sf::Vector2f(WIN_X / 2 - 200, WIN_Y / 2 + (50 * j)));
			game->addAction(new GVAMouseClickCallBack<std::string>(connect_room, *GameInfo::getInstance().mRoomlist.at(j)->name));
			mGameListView.pushObject(game);
			mGameListView.pushObject(game->mText);
			GameInfo::getInstance().mGamelist.push_back(game);
			j++;
		}
	}
	GameInfo::getInstance().mUpdateRooms = PlayerInfo::STATE::DONE;
	GameInfo::getInstance().unlock();
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
	TextureManager::getInstance().loadTexture("refresh", "Sprite/refresh.png");

	delete loading;
	
	//init connect
	GVOButton *button = new GVOButton(sf::Vector2f(WIN_X / 2 - (TextureManager::getInstance().getTexture("connexion").getSize().x * 0.8) / 2, 2 * WIN_Y / 3), TextureManager::getInstance().getTexture("connexion"), sf::Vector2f(0.8, 0.8));
	button->addAction(new GVAMouseClickCallBack<int>(connect, 0));
	mConnectView.pushObject(button);
	button = new GVOButton(sf::Vector2f(WIN_X / 2 - TextureManager::getInstance().getTexture("black").getSize().x * 0.8, WIN_Y / 2), TextureManager::getInstance().getTexture("black"), sf::Vector2f(0.8, 0.8));
	button->addAction(new GVAMouseClickCallBack<std::string>(change_color, std::string("black")));
	mConnectView.pushObject(button);
	button = new GVOButton(sf::Vector2f(WIN_X / 2 + TextureManager::getInstance().getTexture("white").getSize().x * 0.8, WIN_Y / 2), TextureManager::getInstance().getTexture("white"), sf::Vector2f(0.8, 0.8));
	button->addAction(new GVAMouseClickCallBack<std::string>(change_color, std::string("white")));
	mConnectView.pushObject(button);

	mConnectView.pushObject(new GVOText("PSEUDO :", sf::Vector2f(WIN_X / 2 - 150, WIN_Y / 3 - 20)));
	GVOInputBox *ib = new GVOInputBox("", sf::Vector2f(WIN_X / 2 - 50, WIN_Y / 3 - 20), sf::Vector2f(200, 30), PlayerInfo::getInstance().mPseudo, PlayerInfo::getInstance().getMutex());
	ib->addAction(new GVAKeyPressedFocusSave(PlayerInfo::getInstance().mPseudo, PlayerInfo::getInstance().getMutex()));
	ib->addAction(new GVAMouseHoverChangeColor(sf::Color(150, 150, 255, 255), sf::Color(255, 255, 255, 255)));
	mConnectView.pushObject(ib);
	mConnectView.pushObject(new GVOText("HOST :", sf::Vector2f(WIN_X / 2 - 150, WIN_Y / 3 + 50)));
	GVOInputBox *ibh = new GVOInputBox("", sf::Vector2f(WIN_X / 2 - 50, WIN_Y / 3 + 50), sf::Vector2f(200, 30), PlayerInfo::getInstance().mHost, PlayerInfo::getInstance().getMutex());
	ibh->setTextPosition(GVOInputBox::e_position::ALIGN_RIGHT);
	ibh->addAction(new GVAKeyPressedFocusSave(PlayerInfo::getInstance().mHost, PlayerInfo::getInstance().getMutex()));
	ibh->addAction(new GVAMouseHoverChangeColor(sf::Color(150, 150, 255, 255), sf::Color(255, 255, 255, 255)));
	mConnectView.pushObject(ibh);

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
	btn->addAction(new GVAMouseClickCallBack<int>(mute_speaker, 0));
	PlayerInfo::getInstance().lock();
	if (PlayerInfo::getInstance().mMusicMute)
		btn->getSprite().setTextureRect(sf::IntRect(128, 0, 128, 128));
	else
		btn->getSprite().setTextureRect(sf::IntRect(0, 0, 128, 128));
	btn->addAction(new GVAMouseClickTextureRect(sf::IntRect(128, 0, 128, 128), sf::IntRect(0, 0, 128, 128), PlayerInfo::getInstance().mMusicMute));
	PlayerInfo::getInstance().unlock();
	btn->addAction(new GVAMouseHoverChangeColor(sf::Color(sf::Uint8(255), sf::Uint8(255), sf::Uint8(255), sf::Uint8(180)), sf::Color(sf::Uint8(255), sf::Uint8(255), sf::Uint8(255), sf::Uint8(255))));
	mMenuView.pushObject(btn);

	//init home
	GVOText *text = new GVOText("Ah, te revoila !", sf::Vector2f(WIN_X / 2 - 50, WIN_Y / 2 - 10));
	mHomeView.pushObject(text);

	//init options
	text = new GVOText("Musique :", sf::Vector2f(WIN_X / 2 - 150, WIN_Y / 2 - 15));
	mClientOptions.pushObject(text);
	ib = new GVOInputBox("", sf::Vector2f(WIN_X / 2, WIN_Y / 2 - 15), sf::Vector2f(60, 30), PlayerInfo::getInstance().mStringVolume, PlayerInfo::getInstance().getMutex());
	ib->setTextPosition(GVOInputBox::e_position::CENTERED);
	mClientOptions.pushObject(ib);
	btn = new GVOButton(sf::Vector2f(WIN_X / 2 - 51.2, WIN_Y / 2 - 25.2), TextureManager::getInstance().getTexture("speaker"), sf::Vector2f(0.4, 0.4));
	btn->getSprite().setTextureRect(sf::IntRect(256, 0, 128, 128));
	btn->addAction(new GVAMouseHoverChangeColor(sf::Color(sf::Uint8(210), sf::Uint8(255), sf::Uint8(210), sf::Uint8(180)), sf::Color(sf::Uint8(255), sf::Uint8(255), sf::Uint8(255), sf::Uint8(255))));
	btn->addAction(new GVAMouseClickCallBack<float>(change_volume, -10));
	mClientOptions.pushObject(btn);
	btn = new GVOButton(sf::Vector2f(WIN_X / 2 + 70, WIN_Y / 2 - 25.2), TextureManager::getInstance().getTexture("speaker"), sf::Vector2f(0.4, 0.4));
	btn->getSprite().setTextureRect(sf::IntRect(0, 0, 128, 128));
	btn->addAction(new GVAMouseHoverChangeColor(sf::Color(sf::Uint8(210), sf::Uint8(255), sf::Uint8(210), sf::Uint8(180)), sf::Color(sf::Uint8(255), sf::Uint8(255), sf::Uint8(255), sf::Uint8(255))));
	btn->addAction(new GVAMouseClickCallBack<float>(change_volume, +10));
	mClientOptions.pushObject(btn);

	//init gamelist
	btn = new GVOButton(sf::Vector2f(500, 500), TextureManager::getInstance().getTexture("refresh"), sf::Vector2f(1,1));
	btn->addAction(new GVAMouseClickCallBack<PlayerInfo::STATE>(refresh_games, PlayerInfo::STATE::ASK));
	mGameListView.pushObject(btn);

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
		showGames(1);
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
		if (PlayerInfo::getInstance().mConnect == PlayerInfo::STATE::DONE) // Connected to server
		{
			if (GameInfo::getInstance().mConnected == PlayerInfo::STATE::DONE) // Connected to game
				mCurrentView = &mGameView;
			else // List of games
				mCurrentView = &mGameListView;
		}
		else // Connection view
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
	float rVol = (PlayerInfo::getInstance().mMusicMute == true ? 0 : PlayerInfo::getInstance().mMusicVolume);
	if (rVol != mThemeSound.getVolume())
		mThemeSound.setVolume(rVol);
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