#pragma once

#ifndef TEXTURE_MANAGER_HPP_
#define	TEXTURE_MANAGER_HPP_

#include	<SFML/Graphics.hpp>
#include	<string>
#include	<map>

class TextureManager
{
private:
	TextureManager(void);
	std::map<std::string, sf::Texture *> mTextures;

public:
	~TextureManager(void);
	static TextureManager &getInstance(void);

public:
	bool loadTexture(std::string key, std::string path);
	sf::Texture &getTexture(std::string key);
};

#endif // !TEXTURE_MANAGER_HPP_