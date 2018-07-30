//
// Created by black on 02.06.18.
//
#pragma once

#include <SFML/System/Clock.hpp>

class Timer
{
	static sf::Clock clock_;
public:
	static sf::Clock const& getClock()
	{ return clock_; }
};
