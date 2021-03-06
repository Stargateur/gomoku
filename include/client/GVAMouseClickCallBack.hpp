#pragma once

#ifndef MOUSECLICKCALLBACK_HPP_
#define MOUSECLICKCALLBACK_HPP_

#include	<iostream>
#include	<SFML/Graphics.hpp>
#include	"IGVAMouseClick.hpp"

template<typename T>
class GVAMouseClickCallBack : public IGVAMouseClick
{
public:
	GVAMouseClickCallBack(void(*callback)(T), T callbackParam)
	{
		mCallback = callback;
		mCallbackParam = callbackParam;
	}
	virtual ~GVAMouseClickCallBack() {}
	virtual void Act(sf::Sprite &texture, sf::Vector2f const &mousePosition)
	{
		if (mousePosition.x >= texture.getGlobalBounds().left && mousePosition.x <= texture.getGlobalBounds().left + texture.getGlobalBounds().width &&
			mousePosition.y >= texture.getGlobalBounds().top && mousePosition.y <= texture.getGlobalBounds().top + texture.getGlobalBounds().height)
		{
			if (mCallback != nullptr)
				(*mCallback)(mCallbackParam);
		}
	}

private:
	T				mCallbackParam;
	void			(*mCallback)(T param);
};

#endif // !MOUSECLICKCALLBACK_HPP_
