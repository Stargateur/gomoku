#pragma once

#ifndef MOUSECLICKCALLBACK_HPP_
#define MOUSECLICKCALLBACK_HPP_

#include	<SFML/Graphics.hpp>
#include	"IGVAMouseClick.hpp"
#include	<iostream>

template<typename T>
class GVAMouseClickCallBack : public IGVAMouseClick<sf::Sprite &, sf::Vector2f &>
{
public:
	GVAMouseClickCallBack(void(*callback)(T), T &callbackParam)
	{
		mCallback = callback;
		mCallbackParam = callbackParam;
	}
	virtual ~GVAMouseClickCallBack() {}
	virtual void Act(sf::Sprite &texture, sf::Vector2f &mousePosition)
	{
		if (mousePosition.x >= texture.getGlobalBounds().left && mousePosition.x <= texture.getGlobalBounds().left + texture.getGlobalBounds().width &&
			mousePosition.y >= texture.getGlobalBounds().top && mousePosition.y <= texture.getGlobalBounds().top + texture.getGlobalBounds().height)
		{
			std::cout << "Here come the callback;" << std::endl;
			if (mCallback != nullptr)
				(*mCallback)(mCallbackParam);
		}
	}

private:
	T				mCallbackParam;
	void			(*mCallback)(T param);
};

#endif // !MOUSECLICKCALLBACK_HPP_
