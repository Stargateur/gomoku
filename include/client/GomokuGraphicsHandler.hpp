#pragma once

#ifndef GOMOKUGRAPHICSHANDLER_HPP_
#define GOMOKUGRAPHICSHANDLER_HPP_

#include	<string>
#include	<mutex>
#include	<SFML/Graphics.hpp>
#include	"GomokuGraphics.hpp"
#include	"PlayerInfo.hpp"

void		connect(int u);
void		connect_room(std::string room);
void		click_plateau(sf::Vector2f *param);
void		change_color(std::string color);
void		change_view(GomokuGraphics::e_view view);
void		validate_team(int use);
void		mute_speaker(int volume);
void		change_volume(float volume);
void		create_game(PlayerInfo::STATE state);
void		change_gamepage(int modifier);
void		quit_game(int use);
void		toggle_gameparam(int paramid);
void		validate_gameparam(int use);

template<typename T>
bool		LUmutex(T &info, std::mutex &mutex)
{
	T		result;
	mutex.lock();
	result = info;
	mutex.unlock();
	return result;
}

#endif // !GOMOKUGRAPHICSHANDLER_HPP_
