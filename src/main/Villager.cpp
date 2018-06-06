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
			envelope_ = std::make_unique<eng::Envelope>(MainController::getInstance().getPlaces().find("FT")->second);
		}
	}
}

Villager::Villager()
{
	name_ = "Villager_" + std::to_string(counter_);
}

void Villager::consume()
{
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
