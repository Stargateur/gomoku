#pragma once

#ifndef IGVACTION_HPP_
#define IGVACTION_HPP_

#include	<SFML/Graphics.hpp>

template<typename... Args>
class IGVAction
{
public:
	virtual ~IGVAction(void) {};
	virtual void Act(Args... args) = 0;
};

#endif // !IGVACTION_HPP_
