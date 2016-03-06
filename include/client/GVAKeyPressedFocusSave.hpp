#pragma once

#ifndef KEYPRESSEDFOCUSSAVE_HPP_
#define KEYPRESSEDFOCUSSAVE_HPP_

#include	<iostream>
#include	<mutex>
#include	<SFML/Graphics.hpp>
#include	"IGVAKeyPressed.hpp"

class GVAKeyPressedFocusSave : public IGVAKeyPressed
{
public:
	GVAKeyPressedFocusSave(std::string &save, std::mutex &mutex) : mSave(save), mMutex(mutex) {}
	virtual ~GVAKeyPressedFocusSave(void) {}
	virtual void Act(sf::Sprite &texture, sf::Vector2f const &mousePosition, sf::Uint32 const &key)
	{
		if (mousePosition.x >= texture.getGlobalBounds().left && mousePosition.x <= texture.getGlobalBounds().left + texture.getGlobalBounds().width &&
			mousePosition.y >= texture.getGlobalBounds().top && mousePosition.y <= texture.getGlobalBounds().top + texture.getGlobalBounds().height)
		{
			mMutex.lock();
			if ((key >= '0' && key <= '9') || (key >= 'a' && key <= 'z') || (key >= 'A' && key <= 'Z') || key == '.')
				mSave += static_cast<char>(key);
			else if (key == 8)
			{
				if (mSave.size() > 0)
					mSave.pop_back();
			}
			mMutex.unlock();
		}
	}

private:
	std::string	&mSave;
	std::mutex	&mMutex;
};

#endif // !KEYPRESSEDFOCUSSAVE_HPP_
