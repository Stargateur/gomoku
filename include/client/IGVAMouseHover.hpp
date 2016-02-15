#pragma once

#ifndef IGVAMOUSE_HOVER_HPP_
#define IGVAMOUSE_HOVER_HPP_

#include	<SFML\Graphics.hpp>
#include	"IGVAction.hpp"

template<typename... Args>
class IGVAMouseHover : public IGVAction<Args...>
{
public:
	virtual ~IGVAMouseHover(void) {};
	virtual void Act(Args... args) = 0;
};

#endif // !IGVAMOUSE_HOVER_HPP_
