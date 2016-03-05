#include	"TextureManager.hpp"

TextureManager::TextureManager(void) {}

TextureManager::~TextureManager(void)
{
	for (std::pair<std::string, sf::Texture *> pair : mTextures)
	{
		if (pair.second != nullptr)
			delete pair.second;
	}
}

TextureManager&	TextureManager::getInstance(void)
{
	static TextureManager mInstance;
	return mInstance;
}

bool TextureManager::loadTexture(std::string key, std::string path)
{
	if (mTextures.find(key) == mTextures.end())
		mTextures[key] = new sf::Texture();
	return mTextures[key]->loadFromFile(path, sf::IntRect());
}

sf::Texture & TextureManager::getTexture(std::string key)
{
	return *mTextures[key];
}
