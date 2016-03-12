#include	<iostream>
#include	<exception>
#include	<thread>
#include	<SFML/Graphics.hpp>
#include	<SFML/Network.hpp>
#include	<boost/filesystem.hpp>
#include	"Client.hpp"
#include	"PlayerInfo.hpp"
#include	"GameInfo.hpp"
#include	"GomokuGraphics.hpp"

void start_tcpclient()
{
	bool	keepRunning = true;
	bool	wantConnect = false;

	while (keepRunning == true)
	{
		PlayerInfo::getInstance().lock();
		wantConnect = PlayerInfo::getInstance().mConnect == PlayerInfo::STATE::ASK;
		PlayerInfo::getInstance().unlock();
		if (wantConnect == true)
		{
			/*PlayerInfo::getInstance().lock();
			PlayerInfo::getInstance().mConnect = PlayerInfo::STATE::DOING;
			PlayerInfo::getInstance().unlock();*/
			try {
				PlayerInfo::getInstance().lock();
				std::string host(PlayerInfo::getInstance().mHost);
				std::string port(PlayerInfo::getInstance().mPort);
				PlayerInfo::getInstance().unlock();
				GameInfo::getInstance().lock();
				GameInfo::getInstance().mErrorMessage = "";
				GameInfo::getInstance().unlock();
				Client		client(host, port);
				PlayerInfo::getInstance().lock();
				PlayerInfo::getInstance().mConnect = PlayerInfo::STATE::DONE;
				PlayerInfo::getInstance().unlock();
				std::cout << "start run" << std::endl;
				client.run();
				std::cout << "end run" << std::endl;
			}
			catch (std::exception &e) {
				PlayerInfo::getInstance().lock();
				PlayerInfo::getInstance().mConnect = PlayerInfo::STATE::FAILED;
				PlayerInfo::getInstance().mErrorMessage = "Connection error !";
				GameInfo::getInstance().lock();
				GameInfo::getInstance().mErrorMessage = "Impossible de se connecter au serveur !";
				GameInfo::getInstance().unlock();
				std::cout << "Couldn't join server" << std::endl;
				std::cout << e.what() << std::endl;
				PlayerInfo::getInstance().unlock();
			}
		}
		else
		{
			//std::cout << "Wainting client" << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(200));
		}

		PlayerInfo::getInstance().lock();
		keepRunning = !PlayerInfo::getInstance().mQuit == PlayerInfo::STATE::ASK;
		PlayerInfo::getInstance().unlock();
	}
}

void start_ui()
{
	sf::Music test;
	
	boost::filesystem::create_directory("Sound");
	boost::filesystem::create_directory("Sprite");
	boost::filesystem::create_directory("Font");
	if (!test.openFromFile("Sound/theme.ogg"))
	{
		std::cout << "Connecting to FTP...";
		sf::Ftp downloader;
		sf::Ftp::Response resp;
		resp = downloader.connect(sf::IpAddress("ftp.cluster011.ovh.net"), 21);
		if (resp.isOk())
			std::cout << "connected !" << std::endl;
		std::string password;
		std::cout << "Password: ";
		std::cin >> password;
		resp = downloader.login("zwertvfrpm", password);
		if (resp.isOk())
			std::cout << "login ok!" << std::endl;
		resp = downloader.changeDirectory("www/gomoku");
		sf::Ftp::DirectoryResponse directory = downloader.getWorkingDirectory();
		if (directory.isOk())
			std::cout << "Working directory: " << directory.getDirectory() << std::endl;
		std::cout << "Downloading assets...";
		downloader.download("theme.ogg", "./Sound");
		downloader.download("bg.jpg", "./Sprite");
		std::cout << "complete !" << std::endl;
		downloader.disconnect();
	}

	GomokuGraphics gui;

	gui.init();
	gui.run();
}

int				main(void) try
{
	// Initing memory
	PlayerInfo::getInstance().load(PROPERTIES_PATH);
	GameInfo::getInstance();

	// Launching main tasks
	std::thread	tcpclient(start_tcpclient);
	start_ui();

	// Quitting all threads
	PlayerInfo::getInstance().lock();
	PlayerInfo::getInstance().mQuit = PlayerInfo::STATE::ASK;
	PlayerInfo::getInstance().unlock();
	tcpclient.join();

	// end of program
	PlayerInfo::getInstance().save(PROPERTIES_PATH);
	return (0);
}
catch (std::exception &e)
{
	std::cerr << e.what() << std::endl;
}

