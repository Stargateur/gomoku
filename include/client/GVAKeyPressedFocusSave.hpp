#pragma once

#ifndef KEYPRESSEDFOCUSSAVE_HPP_
#define KEYPRESSEDFOCUSSAVE_HPP_

#include	<iostream>
#include	<mutex>
#include	<SFML/Graphics.hpp>
#include	"IGVAKeyPressed.hpp"

bool	alphanumdot(sf::Uint32 const &key)
{
	if ((key >= '0' && key <= '9') || (key >= 'a' && key <= 'z') || (key >= 'A' && key <= 'Z') || key == '.')
		return true;
	return false;
}

class GVAKeyPressedFocusSave : public IGVAKeyPressed
{
public:
	GVAKeyPressedFocusSave(std::string &save, std::mutex &mutex, std::function<bool(sf::Uint32 const &)> f = alphanumdot) : mSave(save), mMutex(mutex), mFunc(f) {}
	virtual ~GVAKeyPressedFocusSave(void) {}
	virtual void Act(sf::Sprite &texture, sf::Vector2f const &mousePosition, sf::Uint32 const &key)
	{
		if (mousePosition.x >= texture.getGlobalBounds().left && mousePosition.x <= texture.getGlobalBounds().left + texture.getGlobalBounds().width &&
			mousePosition.y >= texture.getGlobalBounds().top && mousePosition.y <= texture.getGlobalBounds().top + texture.getGlobalBounds().height)
		{
			mMutex.lock();
			if (mFunc(key))
				mSave += key;
			else if (key == 8)
			{
				if (mSave.size() > 0)
					mSave.pop_back();
			}
			mMutex.unlock();
		}
	}

private:
	std::string								&mSave;
	std::mutex								&mMutex;
	std::function<bool(sf::Uint32 const &)>	mFunc;
};

#endif // !KEYPRESSEDFOCUSSAVE_HPP_
