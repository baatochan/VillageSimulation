//
// Created by black on 02.06.18.
//

#include "include/FeedingTrough.hpp"

FeedingTrough::FeedingTrough(const sf::Vector2f& size, const sf::Vector2f& position)
		: Place(size, position)
{}

FeedingTrough::FeedingTrough()
		: Place({50, 100}, {400, 100})
{
	getShape()->setFillColor(sf::Color::Green);
}

std::string FeedingTrough::getName()
{
	return "Feeding Trough";
}
