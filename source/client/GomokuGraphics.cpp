#include	<cstdlib>
#include	"GomokuGraphics.hpp"
#include	"GomokuGraphicsHandler.hpp"
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

GomokuGraphics::GomokuGraphics()
{
	for (size_t i = 0; i < 19; i++)
		for (size_t j = 0; j < 19; j++)
			mStones[i][j] = nullptr;
}

GomokuGraphics::~GomokuGraphics()
{
	reset();
	delete mWindow;
	if (mThemeSound.getStatus() == sf::Music::Status::Playing)
		mThemeSound.stop();
}

void			GomokuGraphics::backgroundEffects(void)
{
	static sf::Clock			clock;
	static char					effect;
	static const sf::Vector2f	initial(mBackground.getScale());
	sf::Vector2f				movement;
	
	if (clock.getElapsedTime().asSeconds() >= 40)
	{
		effect = (effect - 1) * -1;
		clock.restart();
	}
	movement.x = 0.1 * (clock.getElapsedTime().asSeconds() / 40);
	movement.y = movement.x;
	switch (effect)
	{
	// Zoom in
	case 0:
		mBackground.setScale(initial + movement);
		break;
	// Zoom out
	case 1:
		mBackground.setScale(initial + sf::Vector2f(0.1, 0.1) - movement);
		break;
	}
}

void GomokuGraphics::clearGames()
{
	for (GVOButton *btn : GameInfo::getInstance().mGamelist)
	{
		if (btn->mText != nullptr)
			mGameListView.removeObject(btn->mText);
		mGameListView.removeObject(btn);
		delete btn;
	}
	GameInfo::getInstance().mGamelist.clear();
}

void GomokuGraphics::showGames(void)
{
	GVOButton		*game;
	int				page;

	GameInfo::getInstance().lock();
	page = GameInfo::getInstance().mRoomPage;
	if (GameInfo::getInstance().mUpdateRooms == PlayerInfo::STATE::ASK)
	{
		GameInfo::getInstance().mUpdateRooms = PlayerInfo::STATE::DOING;
		while ((page - 1) * PAGE_GAME_COUNT > GameInfo::getInstance().mRoomlist.size())
			page--;
		if (page < 1)
			page = 1;
		std::cout << "doing page " << page << std::endl;
		clearGames();
		int j = 0;
		for (int i = (page - 1) * PAGE_GAME_COUNT; i < page * PAGE_GAME_COUNT; i++)
		{
			if (i >= GameInfo::getInstance().mRoomlist.size())
				break;
			game = new GVOButton(sf::Vector2f(WIN_X / 2 + 150, WIN_Y / 3 + (WIN_Y / (3 * 5) * j)), TextureManager::getInstance().getTexture("connexion"), sf::Vector2f(1, 1));
			game->mText = new GVOText("#" + *GameInfo::getInstance().mRoomlist.at(j)->name, sf::Vector2f(WIN_X / 2 - 200, WIN_Y / 3 + (WIN_Y / (3 * 5) * j)));
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
	mWindow->setFramerateLimit(60);

	//set loading screen
	GVOText *loading = new GVOText("Loading...");
	loading->setPos(sf::Vector2f(WIN_X / 2 - loading->getText().getGlobalBounds().width / 2, WIN_Y / 2 - loading->getText().getGlobalBounds().height / 2));
	mWindow->draw(*loading->getDrawable());
	mWindow->display();

	//charge texture
	TextureManager::getInstance().loadTexture("background", "Sprite/bg.jpg");
	TextureManager::getInstance().loadTexture("board", "Sprite/board.png");
	TextureManager::getInstance().loadTexture("connexion", "Sprite/connexion.png");
	TextureManager::getInstance().loadTexture("create", "Sprite/creategame.png");
	TextureManager::getInstance().loadTexture("black", "Sprite/black.png");
	TextureManager::getInstance().loadTexture("white", "Sprite/white.png");
	TextureManager::getInstance().loadTexture("histo", "Sprite/histo.png");
	TextureManager::getInstance().loadTexture("home", "Sprite/home.png");
	TextureManager::getInstance().loadTexture("play", "Sprite/play.png");
	TextureManager::getInstance().loadTexture("speaker", "Sprite/speaker.png");
	TextureManager::getInstance().loadTexture("option", "Sprite/options.png");

	delete loading;
	
	//init connect
	mConnectView.pushObject(new GVOText("PSEUDO :", sf::Vector2f(WIN_X / 2 - 150, WIN_Y / 3 - 20)));
	GVOInputBox *ib = new GVOInputBox("", sf::Vector2f(WIN_X / 2 - 50, WIN_Y / 3 - 20), sf::Vector2f(240, 30), PlayerInfo::getInstance().mPseudo, PlayerInfo::getInstance().getMutex());
	ib->addAction(new GVAKeyPressedFocusSave(PlayerInfo::getInstance().mPseudo, PlayerInfo::getInstance().getMutex()));
	ib->addAction(new GVAMouseHoverChangeColor(sf::Color(150, 150, 255, 255), sf::Color(255, 255, 255, 255)));
	mConnectView.pushObject(ib);
	mConnectView.pushObject(new GVOText("HOST :", sf::Vector2f(WIN_X / 2 - 150, WIN_Y / 3 + 50)));
	GVOInputBox *ibh = new GVOInputBox("", sf::Vector2f(WIN_X / 2 - 50, WIN_Y / 3 + 50), sf::Vector2f(150, 30), PlayerInfo::getInstance().mHost, PlayerInfo::getInstance().getMutex());
	ibh->setTextPosition(GVOInputBox::e_position::ALIGN_RIGHT);
	ibh->addAction(new GVAKeyPressedFocusSave(PlayerInfo::getInstance().mHost, PlayerInfo::getInstance().getMutex()));
	ibh->addAction(new GVAMouseHoverChangeColor(sf::Color(150, 150, 255, 255), sf::Color(255, 255, 255, 255)));
	mConnectView.pushObject(ibh);
	mConnectView.pushObject(new GVOText(":", sf::Vector2f(WIN_X / 2 + 107, WIN_Y / 3 + 50)));
	ibh = new GVOInputBox("", sf::Vector2f(WIN_X / 2 + 120, WIN_Y / 3 + 50), sf::Vector2f(70, 30), PlayerInfo::getInstance().mPort, PlayerInfo::getInstance().getMutex());
	ibh->setTextPosition(GVOInputBox::e_position::CENTERED);
	ibh->addAction(new GVAKeyPressedFocusSave(PlayerInfo::getInstance().mPort, PlayerInfo::getInstance().getMutex()));
	ibh->addAction(new GVAMouseHoverChangeColor(sf::Color(150, 150, 255, 255), sf::Color(255, 255, 255, 255)));
	mConnectView.pushObject(ibh);
	GVOButton *button = new GVOButton(sf::Vector2f(WIN_X / 2 - (TextureManager::getInstance().getTexture("connexion").getSize().x * 0.8) / 2, 2 * WIN_Y / 3), TextureManager::getInstance().getTexture("connexion"), sf::Vector2f(0.8, 0.8));
	button->addAction(new GVAMouseClickCallBack<int>(connect, 0));
	mConnectView.pushObject(button);

	//Background
	mBackground.setTexture(TextureManager::getInstance().getTexture("background"));
	mBackground.setScale(sf::Vector2f(0.17, 0.17));
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
	text = new GVOText("Connecte toi à une partie:");
	text->getText().setCharacterSize(42);
	text->getText().setPosition(sf::Vector2f(WIN_X / 2 - text->getText().getGlobalBounds().width / 2, WIN_Y / 3 - 100));
	mGameListView.pushObject(text);
	text = new GVOText("ou Créé la tienne:");
	text->getText().setCharacterSize(42);
	text->getText().setPosition(sf::Vector2f(WIN_X / 2 - text->getText().getGlobalBounds().width / 2, 500));
	mGameListView.pushObject(text);
	GVOInputBox *gameCreate = new GVOInputBox("Room Name", sf::Vector2f(300, 600), sf::Vector2f(200, 30), GameInfo::getInstance().mName, GameInfo::getInstance().getMutex());
	gameCreate->addAction(new GVAKeyPressedFocusSave(GameInfo::getInstance().mName, GameInfo::getInstance().getMutex()));
	gameCreate->addAction(new GVAMouseHoverChangeColor(sf::Color(150, 150, 255, 255), sf::Color(255, 255, 255, 255)));
	mGameListView.pushObject(gameCreate);
	btn = new GVOButton(sf::Vector2f(600, 600), TextureManager::getInstance().getTexture("create"), sf::Vector2f(1, 1));
	btn->addAction(new GVAMouseClickCallBack<PlayerInfo::STATE>(create_game, PlayerInfo::STATE::ASK));
	mGameListView.pushObject(btn);

	//init lobby
	text = new GVOText("Choisis ton équipe :");
	text->getText().setCharacterSize(42);
	text->getText().setPosition(sf::Vector2f(WIN_X / 2 - text->getText().getGlobalBounds().width / 2, WIN_Y / 3 - 100));
	mLobbyView.pushObject(text);
	button = new GVOButton(sf::Vector2f(WIN_X / 2 - TextureManager::getInstance().getTexture("black").getSize().x * 0.8, WIN_Y / 2), TextureManager::getInstance().getTexture("black"), sf::Vector2f(0.8, 0.8));
	button->addAction(new GVAMouseClickCallBack<std::string>(change_color, std::string("black")));
	mLobbyView.pushObject(button);
	button = new GVOButton(sf::Vector2f(WIN_X / 2 + TextureManager::getInstance().getTexture("white").getSize().x * 0.8, WIN_Y / 2), TextureManager::getInstance().getTexture("white"), sf::Vector2f(0.8, 0.8));
	button->addAction(new GVAMouseClickCallBack<std::string>(change_color, std::string("white")));
	mLobbyView.pushObject(button);
	btn = new GVOButton(sf::Vector2f(WIN_X / 2 - 100, WIN_Y * 2 / 3), TextureManager::getInstance().getTexture("connexion"), sf::Vector2f(1, 1));
	btn->addAction(new GVAMouseClickCallBack<int>(validate_team, 0));
	mLobbyView.pushObject(btn);

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
			delete mStones[i][j];
			mStones[i][j] = nullptr;
		}
	}
	clearGames();
}

void GomokuGraphics::run()
{
	sf::String test;
	mClock.restart();
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
		showGames();
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
		mClock.restart();
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
	GameInfo::getInstance().lock();
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
			{
				if (GameInfo::getInstance().mShowLobby == true)
					mCurrentView = &mLobbyView;
				else
					mCurrentView = &mGameView;
			}
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
	GameInfo::getInstance().unlock();
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
