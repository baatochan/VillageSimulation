//
// Created by black on 06.06.18.
//

#include <MainController.hpp>
#include "Villager.hpp"
#include "Envelope.hpp"

void Villager::update()
{
	if ( foodLevel < 50 || waterLevel < 50)
	{
		if ( !(envelope_  && envelope_->target->getName() == "Feeding Trough") )
		{
			spdlog::get("main")->debug("{} is hungry/thirsty.", name_);
			setOrder(Engine::Envelope{
					MainController::getInstance().getPlaces().find("FT")->second
					, "Refill"
					, 100});
		}
	}
}

Villager::Villager()
{
	name_ = "Villager_" + std::to_string(counter_);
}

void Villager::consume()
{
	std::lock_guard <std::mutex> lockGuardFood(foodMutex);
	std::lock_guard <std::mutex> lockGuardWater(drinkMutex);

	if ( !lastRefreshInterval )
	{
		lastRefreshInterval = Timer::getClock().getElapsedTime();
		return;
	}

	auto currentTime = Timer::getClock().getElapsedTime();
	auto delta = currentTime - *lastRefreshInterval;

	foodLevel -= (delta.asSeconds()*hunger);
	waterLevel -= (delta.asSeconds()*thirst);

	lastRefreshInterval = currentTime;

	if ( foodLevel < 0 || waterLevel < 0 )
	{
		spdlog::get("main")->info("{} have died horrible death.", name_);
		available_ = false;
	}

}

void Villager::refillFood(int amount)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(10*amount));

	std::lock_guard<std::mutex> lockGuard(foodMutex);
	foodLevel += amount;
}

void Villager::refillWater(int amount)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(5*amount));

	std::lock_guard<std::mutex> lockGuard(drinkMutex);
	waterLevel += amount;
}

float Villager::getWaterLevel() const
{
	return waterLevel;
}

float Villager::getFoodLevel() const
{
	return foodLevel;
}

bool Villager::isHungry()
{
	return foodLevel < 50 || waterLevel < 50;
}
