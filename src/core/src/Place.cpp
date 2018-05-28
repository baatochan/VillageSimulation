//
// Created by black on 27.05.18.
//

#include "Place.hpp"

sf::Drawable* Engine::Place::getDrawable()
{
	return drawable_.get();
}

Engine::Place::Place(sf::Vector2f const &size, sf::Vector2f const &position)
{
	drawable_ = std::make_shared<sf::RectangleShape>();
	drawable_->setSize(size);
	drawable_->setPosition(position);
}

std::string const &Engine::Place::getName()
{
	return name;
}
