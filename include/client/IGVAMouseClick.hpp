#pragma once

#ifndef IGVAMOUSE_CLICK_HPP_
#define IGVAMOUSE_CLICK_HPP_

#include	<SFML/Graphics.hpp>
#include	"IGVAction.hpp"

template<typename... Args>
class IGVAMouseClick : public IGVAction<Args...>
{
public:
	virtual ~IGVAMouseClick(void) {};
	virtual void Act(Args... args) = 0;
};

#endif // !IGVAMOUSE_CLICK_HPP_
