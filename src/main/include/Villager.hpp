//
// Created by black on 06.06.18.
//

#pragma once


#include <Agent.hpp>
#include "Timer.hpp"

class Villager
		: public eng::Agent
{
	const float hunger{0.4};
	const float thirst{0.7};
protected:
	std::optional<sf::Time> lastRefreshInterval{};
	float foodLevel{20};
	float waterLevel{20};
protected:
	void update() override;
public:
	void consume();
	Villager();
};

