//
// Created by black on 27.05.18.
//

#include "Place.hpp"

sf::Shape* Engine::Place::getShape()
{
	return drawable_.get();
}

Engine::Place::Place(sf::Vector2f const &size, sf::Vector2f const &position)
{
	drawable_ = std::make_shared<sf::RectangleShape>();
	drawable_->setSize(size);
	drawable_->setPosition(position);
	drawable_->setFillColor(sf::Color::Black);
}

std::string Engine::Place::getName() const
{
	return std::string{"Place"};
}
