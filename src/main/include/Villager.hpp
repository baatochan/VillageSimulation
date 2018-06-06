//
// Created by black on 06.06.18.
//

#pragma once


#include <Agent.hpp>
#include "Timer.hpp"

class Villager
		: public eng::Agent
{
protected:
	sf::Time lastRefreshInterval{Timer::getClock().getElapsedTime()};
	float foodLevel{100};
	float waterLevel{100};
protected:
	void update() override;
public:

	Villager();
};

