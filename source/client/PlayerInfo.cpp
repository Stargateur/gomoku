#include	<iostream>
#include	<boost/property_tree/ptree.hpp>
#include	<boost/property_tree/ini_parser.hpp>
#include	<boost/filesystem.hpp>
#include	"PlayerInfo.hpp"

PlayerInfo::PlayerInfo() : mQuit(NOTHING), mDisconnect(NOTHING), mConnect(NOTHING), mWantPlay(NOTHING), mColor("black"),
mView(GomokuGraphics::e_view::HOME), mMusicVolume(70), mMusicMute(false), mStringVolume("70")
{
}

PlayerInfo::~PlayerInfo()
{
}

PlayerInfo & PlayerInfo::getInstance(void)
{
	static PlayerInfo instance;
	return instance;
}

void PlayerInfo::load(std::string const & path)
{
	boost::property_tree::ptree		tree;

	// check if file exist
	FILE *fp = fopen(path.c_str(), "a+");
	fclose(fp);

	// load configuration
	try {
		boost::property_tree::ini_parser::read_ini(path, tree);
		mPseudo = tree.get<std::string>("Config.pseudo", "Player");
		mHost = tree.get<std::string>("Config.host", "localhost");
		mMusicVolume = tree.get<float>("Config.musicVolume", 70);
		mStringVolume = std::to_string(static_cast<int>(mMusicVolume));
		mMusicMute = tree.get<bool>("Config.musicMute", false);
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
}

void PlayerInfo::save(std::string const & path)
{
	boost::property_tree::ptree		tree;

	// check if file exist
	FILE *fp = fopen(path.c_str(), "a+");
	fclose(fp);

	// save configuration
	try {
		boost::property_tree::ini_parser::read_ini(path, tree);
		tree.put<std::string>("Config.pseudo", mPseudo);
		tree.put<std::string>("Config.host", mHost);
		tree.put<float>("Config.musicVolume", mMusicVolume);
		tree.put<bool>("Config.musicMute", mMusicMute);
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
		getchar();
	}
	boost::property_tree::ini_parser::write_ini(path, tree);
}

void PlayerInfo::lock(void)
{
	mMutex.lock();
}

void PlayerInfo::unlock(void)
{
	mMutex.unlock();
}

std::mutex &PlayerInfo::getMutex(void)
{
	return mMutex;
}
