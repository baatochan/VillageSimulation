//
// Created by black on 02.06.18.
//

#include <spdlog/spdlog.h>
#include "include/FeedingTrough.hpp"
#include "Agent.hpp"

FeedingTrough::FeedingTrough(const sf::Vector2f& size, const sf::Vector2f& position)
		: Place(size, position)
{}

FeedingTrough::FeedingTrough()
		: Place({50, 100}, {100, 100})
{
	getShape()->setFillColor(sf::Color::Green);
}

std::string FeedingTrough::getName() const
{
	return "Feeding Trough";
}

void FeedingTrough::execute(eng::Agent const& agent)
{
	spdlog::get("main")->debug("{} reached {}.", agent.getName(), getName());
}
