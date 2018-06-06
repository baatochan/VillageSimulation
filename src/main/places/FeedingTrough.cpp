//
// Created by black on 02.06.18.
//

#include <spdlog/spdlog.h>
#include <MainController.hpp>
#include "include/FeedingTrough.hpp"
#include "Agent.hpp"

FeedingTrough::FeedingTrough(const sf::Vector2f& size, const sf::Vector2f& position)
		: Place(size, position)
{}

FeedingTrough::FeedingTrough()
		: Place({50, 100}, {400, 400})
{
	getShape()->setFillColor(sf::Color::Green);
}

std::string FeedingTrough::getName() const
{
	return "Feeding Trough";
}

void FeedingTrough::execute(eng::Agent* agent)
{
	spdlog::get("main")->debug("{} reached {}.", agent->getName(), getName());

	if ( agent->getEnvelope()->message == "Refill" )
	{
		spdlog::get("main")->debug("{} desired to feast.", agent->getName());
		feast(dynamic_cast<Villager*>(agent));
	}
}

void FeedingTrough::feast(Villager* villager)
{
	std::unique_lock<std::mutex> uniqueLock(stoolsMutex_);

	if ( stools_.size() >= availableStools_ )
	{
		spdlog::get("main")->debug("Little he knew, that all of stools were taken.");

		subHolder_.wait_for(uniqueLock, std::chrono::seconds(10),
				[&](){ return stools_.size() < availableStools_; }
				);
		if ( stools_.size() >= availableStools_ )
			return;
		spdlog::get("main")->debug("{} have been allowed to enter."
				, villager->getName()
		);
	}

	stools_.push_back(villager);

	uniqueLock.unlock();

	auto consume = 1;
	while ( villager->getFoodLevel() <= villager->getEnvelope()->amount
			|| villager->getWaterLevel() <= villager->getEnvelope()->amount
			)
	{
		eat(villager, consume);
		drink(villager, consume);
	}

	uniqueLock.lock();
	spdlog::get("main")->debug(
			"Full of strength, {} returned to work."
			, villager->getName()
	);
	stools_.remove(villager);
	uniqueLock.unlock();

	villager->setOrder(
			eng::Envelope{ MainController::getInstance().getPlaces().find("RL")->second }
	);

	subHolder_.notify_one();
}

void FeedingTrough::drink(Villager *villager, int amount)
{
	std::lock_guard<std::mutex> lockGuard(waterMutex_);

	waterAmount_ -= amount;
	villager->refillWater(amount);
}

void FeedingTrough::eat(Villager *villager, int amount)
{
	std::lock_guard<std::mutex> lockGuard(foodMutex_);

	foodAmount_ -= amount;
	villager->refillFood(amount);
}
