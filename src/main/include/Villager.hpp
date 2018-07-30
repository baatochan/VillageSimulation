//
// Created by black on 06.06.18.
//

#pragma once


#include <Agent.hpp>
#include "Timer.hpp"

class Villager
		: public eng::Agent
{
	const float hunger{0.4f};
	const float thirst{0.7f};
protected:
	std::optional<sf::Time> lastRefreshInterval{};
	std::mutex foodMutex;
	std::mutex drinkMutex;

	float foodLevel{20};
	float waterLevel{20};
protected:
	void update() override;
public:
	Villager();

	void consume();
	void refillFood(int amount);
	void refillWater(int amount);

	float getFoodLevel() const;
	float getWaterLevel() const;
	bool isHungry();
};

